SET QUOTED_IDENTIFIER OFF
GO

DROP PROCEDURE IF EXISTS spBsp_Tabelle_Select 
GO 

PRINT N'CREATE PROCEDURE spBsp_Tabelle_Select' 
GO 

CREATE PROCEDURE dbo.spBsp_Tabelle_Select
(
  -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
    @nKey                   BIGINT          = NULL  
      
  -- Nettodaten
  -- --------------------------------------------------------------------------------
 
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

  Prozedur  : spBsp_Tabelle_Select

  Aufgabe   : Selectiert die tblBsp_Tabelle

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
                     
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
     Daten aufbereiten
  ********************************************************************************/

  /********************************************************************************
     Resultset
  ********************************************************************************/
  IF @nDebug > 1 SELECT 'spBsp_Tabelle_Select Start Result', GETUTCDATE()

  SELECT  nKey
        , szBeispiel
        , szComment
        , dtLastModified
        , szUserModified 
  FROM tblBsp_Tabelle (NOLOCK) 
  WHERE nKey = ISNULL(@nKey, nKey)

  IF @nDebug > 0 SELECT N'spBsp_Tabelle_Select End', GETUTCDATE(), @nError AS N'nError', @szError AS N'szError'

END 

GO 
