SET QUOTED_IDENTIFIER OFF
GO

DROP PROCEDURE IF EXISTS spBsp_TabelleHistory_Maintanance 
GO 

PRINT N'CREATE PROCEDURE spBsp_TabelleHistory_Maintanance' 
GO 


CREATE PROCEDURE dbo.spBsp_TabelleHistory_Maintanance
(
  -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
    @nMaximumAmount               INT             

  -- Nettodaten
  -- --------------------------------------------------------------------------------

  -- Verwaltungsinformationen
  -- --------------------------------------------------------------------------------
  , @szUserName                   NVARCHAR(64)                    -- User, der den Eintrag tätigt
  , @nLanguageId                  INT             = -1            -- Sprache für die projektiert werden soll (kann von usersprache abweichen)
  , @bNoResultSet                 INT             = 0             -- Optional: gibt an, ob Resultset gewünscht ist
  , @nDebug                       INT             = 0             -- Debugflag
  , @nError                       INT             = 0     OUTPUT  -- Optional, Rückgabe: Lieferung Fehler zur übergeordneten Abfrage 
  , @szError                      NVARCHAR(256)   = N''   OUTPUT  -- Optional, Rückgabe: Fehlertext  
)
/****************************************************************************

  Prozedur  : spBsp_TabelleHistory_Maintanance

  Aufgabe   : Löscht die Einträge aus der Historisierungstabelle tblBsp_TabelleHistory bis auf @nMaximumAmount Einträge
              Dabei werden Max 300000 Einträgen auf einmal gelöscht 

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
                     
****************************************************************************/
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

  IF @nDebug > 0 SELECT N'spBsp_TabelleHistory_Maintanance Start', GETUTCDATE()
  /********************************************************************************
    Variablen deklarieren
  ********************************************************************************/      
  DECLARE @bUseTransaction      INT         = 0
  DECLARE @szOwnSPName          SYSNAME     = OBJECT_NAME(@@procid)
  DECLARE @dtNow                DATETIME2   = dbo.fnSys_Now()
  DECLARE @dtMin                DATETIME2   = dbo.fnSys_Min()
  DECLARE @nCount               INT         = 0
  DECLARE @nRowsToDelete		    BIGINT			= 300000    -- MaxAnzahl der zu löschenden Datensätze pro Durchgang
  DECLARE @nMinId		            BIGINT			= 0

  /********************************************************************************
    Transaktion öffnen
  ********************************************************************************/
  SELECT  @bUseTransaction = (CASE WHEN @@TRANCOUNT > 0 THEN 0 ELSE 1 END)
  IF (1 = @bUseTransaction) BEGIN TRANSACTION @szOwnSPName     
 
  BEGIN TRY  
  
    -- Das selbe wie Select Count (*) aber wesentlich schneller!!
    SELECT @nCount = st.row_count FROM sys.dm_db_partition_stats st (NOLOCK) WHERE (object_name(object_id, db_id(DB_NAME())) = 'tblBsp_TabelleHistory') AND (st.index_id < 2) 

      -- Anzahl größer als die Maximalzahl erlaubter Einträge
    IF (@nCount > @nMaximumAmount) BEGIN
      -- kleinsten nKey suchen
      SELECT @nMinId = MIN(nKey) FROM tblBsp_TabelleHistory (NOLOCK)
      -- ermitteln der Anzahl zu löschender Datensätze, jedoch maximal nRowsToDelete
      IF (@nCount - @nRowsToDelete > @nMaximumAmount) BEGIN
        SET @nMinId = @nMinId + @nRowsToDelete
      END ELSE BEGIN
        SET @nMinId = @nMinId + @nCount - @nMaximumAmount
      END
      -- eigentliches löschen der Datensätze
      DELETE FROM tblBsp_TabelleHistory WHERE nKey < @nMinId
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
    END ELSE BEGIN 
      SELECT st.row_count AS nLeftover FROM sys.dm_db_partition_stats st (NOLOCK) WHERE (object_name(object_id, db_id(DB_NAME())) = 'tblBsp_TabelleHistory') AND (st.index_id < 2) 
    END
  END
  IF @nDebug > 0 SELECT N'spBsp_TabelleHistory_Maintanance End', GETUTCDATE(), @nError AS N'nError', @szError AS N'szError'

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

