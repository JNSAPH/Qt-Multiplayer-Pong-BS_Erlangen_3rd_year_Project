SET QUOTED_IDENTIFIER OFF
GO

WHILE EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'spHistoryTrigger_Create')) 
  DROP PROCEDURE spHistoryTrigger_Create 
GO

PRINT N'CREATE PROCEDURE spHistoryTrigger_Create' 
GO

CREATE PROCEDURE dbo.spHistoryTrigger_Create
(
 -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
    @szTableName            NVARCHAR(64)  --z.B. 'tblPM_Employee'
  , @szPath                 NVARCHAR(256) --Ganzer Pfad (auf Ordner), SSMS braucht Schreibberechtigung für Dateipfad
  , @szPrimaryKey           NVARCHAR(32)  --Name der PrimaryKey Spalte z.B. 'nKey'
  , @szCombinedPrimaryKey   NVARCHAR(32)    = NULL --Wenn vorhanden Name des zweiten PrimaryKeys
      
  -- Nettodaten
  -- --------------------------------------------------------------------------------
 
  -- Verwaltungsinformationen
  -- --------------------------------------------------------------------------------
  , @szUserName             NVARCHAR(64)    = ''            -- User, der den Eintrag tätigt
  , @nLanguageId            INT             = -1            -- Sprache für die projektiert werden soll (kann von usersprache abweichen)
  , @bNoResultSet           INT             = 0             -- Optional: gibt an, ob Resultset gewünscht ist
  , @nDebug                 INT             = 0             -- Debugflag
  , @szDebug                NVARCHAR(256)   = 0             -- Debugtext
  , @nError                 INT             = 0     OUTPUT  -- Optional, Rückgabe: Lieferung Fehler zur übergeordneten Abfrage 
  , @szError                NVARCHAR(256)   = N''   OUTPUT  -- Optional, Rückgabe: Fehlertext
)
/********************************************************************************

  Prozedur  : spHistoryTrigger_Create

  Aufgabe   : Erstellt eine SP die Skripte für eine Hisotry Tabelle und die dazugehörigen Trigger ausgibt

  Historie  : 28.01.2020  JM  Erstellt
                     
********************************************************************************/
AS
BEGIN

    /********************************************************************************
       Standard Eröffnung
    ********************************************************************************/
    SET ROWCOUNT 0
    SET NOCOUNT ON
    SET QUOTED_IDENTIFIER OFF
    SET TRANSACTION ISOLATION LEVEL SERIALIZABLE 
    SET XACT_ABORT ON 

    IF @nDebug > 0 SELECT N'spBsp_Tabelle_Select Start', GETUTCDATE()

    /********************************************************************************
    Prüfungen
    ********************************************************************************/
    IF NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = @szTableName) BEGIN 
      SELECT  @nError   = 1 -- Fehlernummmer
				    , @szError  = @szTableName + ' exsitiert nicht' -- Fehlertext
      GOTO  spExit   
    END

    IF NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @szTableName AND COLUMN_NAME = @szPrimaryKey) BEGIN 
      SELECT  @nError   = 2 -- Fehlernummmer
				    , @szError  = @szPrimaryKey + ' exsitiert nicht' -- Fehlertext
      GOTO  spExit   
    END

    IF NOT EXISTS (SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @szTableName AND COLUMN_NAME = @szCombinedPrimaryKey)
    AND @szCombinedPrimaryKey IS NOT NULL BEGIN 
      SELECT  @nError   = 3 -- Fehlernummmer
				    , @szError  = @szCombinedPrimaryKey + ' exsitiert nicht' -- Fehlertext
      GOTO  spExit   
    END

    /********************************************************************************
    Variablen Initialisieren und temporäre Tabelle erstellen
    ********************************************************************************/
    DECLARE @tblColumns                       TABLE               (szColumnName CHAR(32), szDataType CHAR(32), szDefault CHAR(32), szColumnNameOriginal NVARCHAR(32))
    DECLARE @szTableHistoryColumnSpec         NVARCHAR(MAX)       = ''
    DECLARE @cmd                              NVARCHAR(256) = ''
    DECLARE @szTriggerColumnsTableHistory     NVARCHAR(MAX)       = N'szAction'   
    DECLARE @szTriggerColumnsTable            NVARCHAR(MAX)       = N''
    CREATE TABLE ##temp(skript NVARCHAR(MAX))
    /********************************************************************************
    Skriptvorlagen
    ********************************************************************************/
    DECLARE @szTemplateHistoryTable NVARCHAR(MAX) = 'SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO


/****************************************************************************

  Tabelle   : @TBL

  Aufgabe   : %TSK

  Historie  : %LOG

****************************************************************************/
PRINT N''@TBL : Tabelle erstellen ''

IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N''@TBL'')) BEGIN
  PRINT N''@TBL : Tabelle wird erstellt ''

  CREATE TABLE dbo.@TBL(
@COL

  CONSTRAINT PK_tblBsp_TabelleHistory PRIMARY KEY CLUSTERED 
  (
	  nKey ASC
  )WITH  FILLFACTOR = 100
  ) 
  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N''@TBL'')) BEGIN
    PRINT N''@TBL : Tabelle wurde erfolgreich erstellt ''
  END
  ELSE BEGIN
    PRINT N''@TBL : Tabelle konnte nicht erstellt werden ''
  END
END
ELSE BEGIN
  PRINT N''@TBL : Tabelle existiert bereits ''
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO'

    DECLARE @szTemplateTrigger NVARCHAR(MAX) ='SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

WHILE EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N''%TRG'')) 
  DROP TRIGGER %TRG 
GO 

/****************************************************************************

  Trigger   : %TRG
  
  Aufgabe   : %TSK
      
  Historie  : %LOG
              
****************************************************************************/
PRINT ''%TRG : Trigger erstellen ''
   
IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = object_id(''%TRG''))BEGIN
  Print ''%TRG : Trigger wird erstellt ''
  
  EXECUTE
  ("
    CREATE TRIGGER %TRG
      ON  %@TBLO
      AFTER %EVET  
    AS 
    BEGIN
      INSERT INTO %@TBLH(%@COLHIST)
      SELECT                            N''%ACTN''%@COLORG
      FROM %EVTED
    END 
  ")

  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(''%TRG'')) BEGIN
    PRINT ''%TRG : Trigger wurde erfolgreich erstellt ''
  END
  ELSE BEGIN
    PRINT ''%TRG : Trigger konnte nicht erstellt werden ''
  END
END
ELSE BEGIN
  PRINT ''%TRG : Trigger existiert bereits ''
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO'

    /********************************************************************************
    Spalteninformationen der Originaltabelle und Ergänzungen als SQL Befehle speichern
    ********************************************************************************/
    INSERT INTO @tblColumns (szColumnName, szDataType, szDefault, szColumnNameOriginal)
    EXEC ( N'SELECT CASE WHEN COLUMN_NAME = ''' + @szPrimaryKey + ''' THEN ''nTableID'' 
           ELSE CASE WHEN COLUMN_NAME = ''' + @szCombinedPrimaryKey + ''' THEN ''nCombinedTableID'' ELSE COLUMN_NAME END END
           ,DATA_TYPE + CASE WHEN CHARACTER_MAXIMUM_LENGTH IS NULL THEN N'''' ELSE N''('' + CONVERT(NVARCHAR(64), CHARACTER_MAXIMUM_LENGTH) + N'')'' END 
           ,REPLACE(REPLACE(COLUMN_DEFAULT, N''('', N''''), N'')'', N'''')
           ,COLUMN_NAME
           FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = ''' + @szTableName + '''') 

    SET @szTableHistoryColumnSpec = ' ' + CAST('nKey' AS CHAR(32)) + CAST('BIGINT' AS CHAR(32)) + 'NOT NULL  IDENTITY(1,1)'
    SET @szTableHistoryColumnSpec += CHAR(13) + CHAR(10) + ',' + CAST('szAction' AS CHAR(32)) + CAST('NVARCHAR(32)' AS CHAR(32)) + 'NOT NULL  DEFAULT N'''''

    SELECT @szTableHistoryColumnSpec += CHAR(13) + CHAR(10) + ',' + szColumnName + szDataType + 'NOT NULL  ' 
                                     + CASE WHEN szColumnName = @szPrimaryKey OR szColumnName = @szCombinedPrimaryKey 
                                     THEN '' 
                                     ELSE ISNULL('DEFAULT ' + szDefault, '') END
    FROM @tblColumns

    /********************************************************************************
    Skript der historischen Tablle anlegen
    ********************************************************************************/
    SET @szTemplateHistoryTable = REPLACE(@szTemplateHistoryTable, '@TBL', @szTableName + 'History')
    SET @szTemplateHistoryTable = REPLACE(@szTemplateHistoryTable, '%TSK', N'Erstellt die historisierungstabelle zu ' + @szTablename)
    SET @szTemplateHistoryTable = REPLACE(@szTemplateHistoryTable, '%LOG', CONVERT(VARCHAR(8), GETUTCDATE(), 4) + '  spHistoryTrigger_Create Automatisch Erstellt')
    SET @szTemplateHistoryTable = REPLACE(@szTemplateHistoryTable, '@COL', @szTableHistoryColumnSpec)

    /********************************************************************************
    Skripte der Trigger erstellen
    ********************************************************************************/
    --Allgemeine Paramter für alle Trigger
    SELECT @szTriggerColumnsTableHistory += ', ' + RTRIM(szColumnName) FROM @tblColumns
    SELECT @szTriggerColumnsTable += ', ' + szColumnNameOriginal FROM @tblColumns
    SET @szTemplateTrigger = REPLACE(@szTemplateTrigger, '%LOG', CONVERT(VARCHAR(8), GETUTCDATE(), 4) + '  spHistoryTrigger_Create Automatisch Erstellt')
    SET @szTemplateTrigger = REPLACE(@szTemplateTrigger, '%@TBLO' , @szTableName)
    SET @szTemplateTrigger = REPLACE(@szTemplateTrigger, '%@TBLH', @szTableName + 'History')
    SET @szTemplateTrigger = REPLACE(@szTemplateTrigger, '%@COLHIST', @szTriggerColumnsTableHistory)
    SET @szTemplateTrigger = REPLACE(@szTemplateTrigger, '%@COLORG', @szTriggerColumnsTable)

    --Trigger Insert erstellen
    DECLARE @szTriggerInsertName NVARCHAR(32) = STUFF(@szTableName, 1, 3, 'tr') + '_Insert'
    DECLARE @szScriptTriggerInsert NVARCHAR(MAX) = REPLACE(@szTemplateTrigger, '%TRG', @szTriggerInsertName)
    SET @szScriptTriggerInsert = REPLACE(@szScriptTriggerInsert, '%TSK', 'Erstellt einen Trigger, der beim Einfuegen in die Tabelle ' + @szTableName +
                                                                         ' einen Eintrag in die Tabelle ' + @szTableName + 'History taetigt')
    SET @szScriptTriggerInsert = REPLACE(@szScriptTriggerInsert, '%EVET', 'INSERT')
    SET @szScriptTriggerInsert = REPLACE(@szScriptTriggerInsert, '%EVTED', 'INSERTED')
    SET @szScriptTriggerInsert = REPLACE(@szScriptTriggerInsert, '%ACTN', 'Insert')

    --Trigger Update erstellen
    DECLARE @szTriggerUpdateName NVARCHAR(32) = STUFF(@szTableName, 1, 3, 'tr') + '_Update'
    DECLARE @szScriptTriggerUpdate NVARCHAR(MAX) = REPLACE(@szTemplateTrigger, '%TRG', @szTriggerUpdateName)
    SET @szScriptTriggerUpdate = REPLACE(@szScriptTriggerUpdate, '%TSK', 'Erstellt einen Trigger, der beim aktualisieren der Tabelle ' + @szTableName +
                                                                         ' einen Eintrag in die Tabelle ' + @szTableName + 'History taetigt')
    SET @szScriptTriggerUpdate = REPLACE(@szScriptTriggerUpdate, '%EVET', 'UPDATE')
    SET @szScriptTriggerUpdate = REPLACE(@szScriptTriggerUpdate, '%EVTED', 'INSERTED')
    SET @szScriptTriggerUpdate = REPLACE(@szScriptTriggerUpdate, '%ACTN', 'Update')

    --Trigger Delete erstellen
    DECLARE @szTriggerDeleteName NVARCHAR(32) = STUFF(@szTableName, 1, 3, 'tr') + '_Delete'
    DECLARE @szScriptTriggerDelete NVARCHAR(MAX) = REPLACE(@szTemplateTrigger, '%TRG', @szTriggerDeleteName)
    SET @szScriptTriggerDelete = REPLACE(@szScriptTriggerDelete, '%TSK', 'Erstellt einen Trigger, der beim löschen aus der Tabelle ' + @szTableName +
                                                                 ' einen Eintrag in die Tabelle ' + @szTableName + 'History taetigt')
    SET @szScriptTriggerDelete = REPLACE(@szScriptTriggerDelete, '%EVET', 'DELETE')
    SET @szScriptTriggerDelete = REPLACE(@szScriptTriggerDelete, '%EVTED', 'DELETED')
    SET @szScriptTriggerDelete = REPLACE(@szScriptTriggerDelete, '%ACTN', 'Delete')

    /********************************************************************************
    Erstellte Skripte im gewünschten Verzeichnis speichern
    ********************************************************************************/
    --History Tabelle
    INSERT INTO ##temp VALUES (@szTemplateHistoryTable) 
    SET @cmd =  'bcp "SELECT * FROM ##temp" queryout ' + @szPath + '\' + @szTableName + 'History.sql ' + '-T -c '
    EXEC xp_cmdshell @cmd
    DELETE FROM ##temp

    --Insert Trigger
    INSERT INTO ##temp VALUES (@szScriptTriggerInsert) 
    SET @cmd =  'bcp "SELECT * FROM ##temp" queryout ' + @szPath + '\' + @szTriggerInsertName + '.sql ' + '-T -c '
    EXEC xp_cmdshell @cmd
    DELETE FROM ##temp

    --Update Trigger
    INSERT INTO ##temp VALUES (@szScriptTriggerUpdate) 
    SET @cmd =  'bcp "SELECT * FROM ##temp" queryout ' + @szPath + '\' + @szTriggerUpdateName + '.sql ' + '-T -c '
    EXEC xp_cmdshell @cmd
    DELETE FROM ##temp

    --Delete Trigger
    INSERT INTO ##temp VALUES (@szScriptTriggerDelete) 
    SET @cmd =  'bcp "SELECT * FROM ##temp" queryout ' + @szPath + '\' + @szTriggerDeleteName + '.sql ' + '-T -c '
    EXEC xp_cmdshell @cmd
    DELETE FROM ##temp

    DROP TABLE ##temp

spExit: 

    /********************************************************************************
    Ende der Prozedur, Resultset bilden wenn gewünscht
    ********************************************************************************/
    IF (@bNoResultSet = 0) BEGIN 
      IF (@nError <> 0) BEGIN
        SELECT  @nError AS N'nError', @szError AS N'szError'
      END
    END
    IF @nDebug > 0 SELECT N'spBsp_Tabelle_Delete End', GETUTCDATE(), @nError AS N'nError', @szError AS N'szError'

    RETURN

END
