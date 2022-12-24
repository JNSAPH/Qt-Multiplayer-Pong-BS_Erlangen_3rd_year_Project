SET QUOTED_IDENTIFIER OFF
GO

DROP PROCEDURE IF EXISTS spBsp_Tabelle_InsertUpdate 
GO 

PRINT N'CREATE PROCEDURE spBsp_Tabelle_InsertUpdate' 
GO 

CREATE PROCEDURE dbo.spBsp_Tabelle_InsertUpdate
(
  -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
    @nKey                   BIGINT          = NULL  OUTPUT

  -- Nettodaten
  -- --------------------------------------------------------------------------------
  , @szBeispiel             NVARCHAR(50)    = NULL
  , @szComment              NVARCHAR(256)   = NULL

  -- Verwaltungsinformationen
  -- --------------------------------------------------------------------------------
  , @szUserName             NVARCHAR(64)                    -- User, der den Eintrag tätigt
  , @nLanguageId            INT             = -1            -- Sprache für die projektiert werden soll (kann von usersprache abweichen)
  , @bNoResultSet           INT             = 0             -- Optional: gibt an, ob Resultset gewünscht ist
  , @nDebug                 INT             = 0             -- Debugflag
  , @szDebug                NVARCHAR(256)   = 0             -- Debugtext
  , @nError                 INT             = 0     OUTPUT  -- Optional, Rückgabe: Lieferung Fehler zur übergeordneten Abfrage 
  , @szError                NVARCHAR(256)   = N''   OUTPUT  -- Optional, Rückgabe: Fehlertext  
)
/********************************************************************************

  Prozedur  : spBsp_Tabelle_InsertUpdate

  Aufgabe   : Schreibt oder aktualisiert einen Datensatzes in der tblBsp_Tabelle

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

********************************************************************************/
AS
BEGIN
  /********************************************************************************
     Standard Eroeffnung
  ********************************************************************************/
  SET ROWCOUNT 0
  SET NOCOUNT ON
  SET QUOTED_IDENTIFIER OFF
  SET TRANSACTION ISOLATION LEVEL SERIALIZABLE 
  SET XACT_ABORT ON 

  IF @nDebug > 0 SELECT N'spBsp_Tabelle_InsertUpdate Start', GETUTCDATE()
  /********************************************************************************
    Variablen deklarieren
  ********************************************************************************/      
  DECLARE @bUseTransaction          INT             = 0
  DECLARE @szOwnSPName              SYSNAME         = OBJECT_NAME(@@procid)
  DECLARE @dtNow                    DATETIME2       = dbo.fnSys_Now()
  DECLARE @dtMin                    DATETIME2       = dbo.fnSys_Min()
  DECLARE @szOldServerName          NVARCHAR(4000)  = N''

  /********************************************************************************
    Transaktion öffnen
  ********************************************************************************/
  SELECT  @bUseTransaction = (CASE WHEN @@TRANCOUNT > 0 THEN 0 ELSE 1 END)
  IF (1 = @bUseTransaction) BEGIN TRANSACTION @szOwnSPName     

  /********************************************************************************
    Prüfungen
  ********************************************************************************/
  -- @nKey existiert nicht
  IF  NOT EXISTS (SELECT * FROM tblBsp_Tabelle (NOLOCK) WHERE nKey = @nKey )
      AND @nKey IS NOT NULL BEGIN 
    SELECT  @nError   = 6000 -- Fehlernummmer
				  , @szError  = N'@nKey existiert nicht' -- Fehlertext
    GOTO  spError   
  END

  BEGIN TRY  
  /********************************************************************************
    Insert oder Update
  ********************************************************************************/  
    -- Insert wenn der Eintrag neu ist
    IF @nKey IS NULL BEGIN 
      INSERT INTO tblBsp_Tabelle( szBeispiel              , szComment               , dtLastModified, szUserModified)
      SELECT                      ISNULL(@szBeispiel, N''), ISNULL(@szComment, N'') , @dtNow        , @szUserName                   

      SELECT @nKey = SCOPE_IDENTITY()

    END 
    --Update
    ELSE BEGIN 
      UPDATE TBL
      SET TBL.szBeispiel      = ISNULL(@szBeispiel  , N''   )
        , TBL.szComment       = ISNULL(@szComment   , N''   )
        , TBL.dtLastModified  = @dtNow
        , TBL.szUserModified  = @szUserName
      FROM tblBsp_Tabelle TBL 
      WHERE TBL.nKey = @nKey
   
    END

  END TRY  
  BEGIN CATCH  
       -- Execute error retrieval routine.
      SELECT  @nError   = ERROR_NUMBER()
            , @szError  = ERROR_MESSAGE()
      GOTO  spError   
  END CATCH; 
    
  /********************************************************************************
    Transaktion abschliessen
  ********************************************************************************/
  IF (@bUseTransaction = 1) COMMIT TRANSACTION @szOwnSPName

  -- Erfolg verzeichnen 
  SELECT @nError    = 0 -- erfolgreich abgeschlossen
       , @szError   = N''

spExit: 

  /********************************************************************************
    Ende der Prozedur, Resultset bilden wenn gewünscht
  ********************************************************************************/
  IF (@bNoResultSet = 0) BEGIN 
    IF (@nError <> 0) BEGIN
      SELECT  @nError AS N'nError', @szError AS N'szError'
    END
  END
  IF @nDebug > 0 SELECT N'spBsp_Tabelle_InsertUpdate End', GETUTCDATE(), @nError AS N'nError', @szError AS N'szError'

  RETURN 

spError: 

  /********************************************************************************
    Fehlerbehandlung
  ********************************************************************************/
  WHILE (@@trancount > 0) and (1 = @bUseTransaction) 
    ROLLBACK TRANSACTION @szOwnSPName

  --  zum Ausgang der SP springen 
  GOTO spExit 

END 

GO 
