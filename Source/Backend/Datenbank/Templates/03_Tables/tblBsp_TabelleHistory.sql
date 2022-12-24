SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO


/****************************************************************************

  Tabelle   : tblBsp_TabelleHistory

  Aufgabe   : Beispiel einer historisierung Tabelle 

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

****************************************************************************/
PRINT N'tblBsp_TabelleHistory : Tabelle erstellen '

IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N'tblBsp_TabelleHistory')) BEGIN
  PRINT N'tblBsp_TabelleHistory : Tabelle wird erstellt '

  CREATE TABLE dbo.tblBsp_TabelleHistory(
  -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
    nKey                    BIGINT            NOT NULL  IDENTITY(1,1)           -- eindeutiger Schlüssel der Tabelle
  , nTabelleID              BIGINT            NOT NULL                          -- eindeutiger Schlüssel des Originalen Eintrags aus der Tabelle tblBsp_Tabelle
       
  -- Nettodaten
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
  , szBeispiel              NVARCHAR(50)      NOT NULL  DEFAULT N''             -- Beispielspalte
  , szAction                NVARCHAR(15)      NOT NULL  DEFAULT N''             -- Gibt an durch welche Aktion auf der Originaltabelle der Eintrag erzeugt wurde (Insert/Update/Delete)
                                                                                  
  -- Verwaltungsinformationen                                                   
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
  , szComment               NVARCHAR(256)     NOT NULL  DEFAULT N''             -- Freiers Kommentarfeld
  , dtCreated               DATETIME2         NOT NULL  DEFAULT GETUTCDATE()    -- Zeitpunkt des Erstellens
  , szUserCreated           NVARCHAR(256)     NOT NULL  DEFAULT N''             -- Erstellt von
  , dtLastModified          DATETIME2         NOT NULL  DEFAULT GETUTCDATE()    -- Zeitpunkt des letzten schreibenden Zugriffs
  , szUserModified          NVARCHAR(64)      NOT NULL  DEFAULT N''             -- letzte Änderung durchgeführt von

  CONSTRAINT PK_tblBsp_TabelleHistory PRIMARY KEY CLUSTERED 
  (
	  nKey ASC
  )WITH  FILLFACTOR = 100
  ) 
  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N'tblBsp_TabelleHistory')) BEGIN
    PRINT N'tblBsp_TabelleHistory : Tabelle wurde erfolgreich erstellt '
  END
  ELSE BEGIN
    PRINT N'tblBsp_TabelleHistory : Tabelle konnte nicht erstellt werden '
  END
END
ELSE BEGIN
  PRINT N'tblBsp_TabelleHistory : Tabelle existiert bereits '
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO
