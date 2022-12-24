SET QUOTED_IDENTIFIER OFF
GO

DROP PROCEDURE IF EXISTS spBsp_Recompile
GO

PRINT 'CREATE PROCEDURE spBsp_Recompile'
GO

CREATE  PROCEDURE spBsp_Recompile 
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

  Prozedur  : spBsp_Recompile

  Aufgabe   : Neuübersetzung für alle SPs in der Datenbank veranlassen

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

  IF @nDebug > 0 SELECT N'spBsp_Recompile Start', GETUTCDATE()

  /********************************************************************************
    Variablen deklarieren
  ********************************************************************************/ 
  DECLARE @nIndex   INT     = 0
  DECLARE @MaxIndex INT
  DECLARE @szTable  sysname

  /********************************************************************************
    Recompile aller Tabellen
  ********************************************************************************/ 
  create table #tFetch 
  ( 
    nIndex int not null IDENTITY,
    szTable sysname
    PRIMARY KEY  CLUSTERED (nIndex)
  )
   
  INSERT INTO #tFetch (szTable)
    SELECT name 
    FROM sysobjects WHERE type = 'U' AND name like N'tbl%'

  SELECT @MaxIndex  = Max(nIndex) FROM #tFetch 
   
  WHILE (@nIndex < @MaxIndex)
  BEGIN
    SET ROWCOUNT 1
    SELECT @szTable = szTable FROM #tFetch WHERE nIndex > @nIndex
   
    SET ROWCOUNT 0
    /* Schleife ueber alle vorkommenden Tabellen. alle abhaengigen objekte werden neu uebersetzt */
  
    EXEC sp_recompile @szTable

    SELECT @nIndex = @nIndex + 1
    
  END

  SET ROWCOUNT 0
  SET NOCOUNT OFF
  /********************************************************************************
    Ende der Prozedur
  ********************************************************************************/
  IF @nDebug > 0 SELECT N'spBsp_Recompile End', GETUTCDATE(), @nError AS N'nError', @szError AS N'szError'

END
GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO


