SET QUOTED_IDENTIFIER OFF
GO

DROP PROCEDURE IF EXISTS spBsp_MaintenancePlan 
GO 

PRINT N'CREATE PROCEDURE spBsp_MaintenancePlan' 
GO 


CREATE PROCEDURE dbo.spBsp_MaintenancePlan
(
  -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
  
  -- Nettodaten
  -- --------------------------------------------------------------------------------
  
  -- Verwaltungsinformationen
  -- --------------------------------------------------------------------------------
    @szUserName             NVARCHAR(64)                    -- User, der den Eintrag tätigt
  , @nLanguageId            INT             = -1            -- Sprache für die projektiert werden soll (kann von usersprache abweichen)
  , @bNoResultSet           INT             = 0             -- Optional: gibt an, ob Resultset gewünscht ist
  , @nDebug                 INT             = 0             -- Debugflag
  , @szDebug                NVARCHAR(256)   = 0             -- Debugtext
  , @nError                 INT             = 0     OUTPUT  -- Optional, Rückgabe: Lieferung Fehler zur übergeordneten Abfrage 
  , @szError                NVARCHAR(256)   = N''   OUTPUT  -- Optional, Rückgabe: Fehlertext  
)
AS
/********************************************************************************

  Funktion : spBsp_MaintenancePlan

  Aufgabe  : Ruft sämtliche Maintenance SPs auf um Daten abzulöschen

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

********************************************************************************/
BEGIN
  /********************************************************************************
     Standard Eröffnung
  ********************************************************************************/  
  SET ROWCOUNT 0
  SET NOCOUNT ON
  SET QUOTED_IDENTIFIER OFF
  SET TRANSACTION ISOLATION LEVEL SERIALIZABLE 
  SET XACT_ABORT ON 

  IF @nDebug > 0 SELECT N'spBsp_MaintenancePlan Start', GETUTCDATE()

  /********************************************************************************
    Variablen deklarieren
  ********************************************************************************/ 
  DECLARE @bUseTransaction      INT             = 0
  DECLARE @szOwnSPName          SYSNAME         = OBJECT_NAME(@@PROCID)
  DECLARE @szErrorGes           NVARCHAR(4000)  = N''
  
  /********************************************************************************
    Transaktion öffnen
  ********************************************************************************/
  -- Histdaten löschen  
  SELECT @nError = 0, @szError = N''
  EXEC spBsp_TabelleHistory_Maintanance  @nMaximumAmount = 1000, @szUserName = @szUserName, @nLanguageId = @nLanguageId, @bNoResultSet = 1, @nDebug = @nDebug, @nError = @nError OUTPUT, @szError = @szError OUTPUT
  IF @nError <> 0 SET @szErrorGes = N'spBsp_TabelleHistory_Maintanance: ' + @szError + N' | '

  /********************************************************************************
    Recompile aller Tabellen 
  ********************************************************************************/
  EXEC spSys_Recompile @szUserName = @szUserName, @bNoResultSet = 1

  /********************************************************************************
    Ende der Prozedur, Resultset bilden wenn gewünscht
  ********************************************************************************/
  IF (@bNoResultSet = 0) BEGIN 
    SELECT  @nError     AS nError
          , @szErrorGes AS szError 
  END

  IF @nDebug > 0 SELECT N'spBsp_MaintenancePlan End', GETUTCDATE(), @nError AS N'nError', @szError AS N'szError'

END

GO

