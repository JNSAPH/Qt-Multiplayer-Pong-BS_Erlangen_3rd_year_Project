SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO


/****************************************************************************

  Tabelle   : tblBsp_Tabelle

  Aufgabe   : Legt eine Tabelle mit dem Namen tblBsp_Tabelle an

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

****************************************************************************/
PRINT N'tblBsp_Tabelle : Tabelle erstellen '

IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N'tblBsp_Tabelle')) BEGIN
  PRINT N'tblBsp_Tabelle : Tabelle wird erstellt '

  CREATE TABLE dbo.tblBsp_Tabelle(
  -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
    nKey                    BIGINT            NOT NULL  IDENTITY(1,1)           -- eindeutiger Schlüssel der Tabelle
       
  -- Nettodaten
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
  , szBeispiel              NVARCHAR(50)      NOT NULL  DEFAULT N''
   
  -- Verwaltungsinformationen
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
  , szComment               NVARCHAR(256)     NOT NULL  DEFAULT N''             -- Freiers Kommentarfeld
  , dtCreated               DATETIME2         NOT NULL  DEFAULT GETUTCDATE()    -- Zeitpunkt des Erstellens
  , szUserCreated           NVARCHAR(256)     NOT NULL  DEFAULT N''             -- Erstellt von
  , dtLastModified          DATETIME2         NOT NULL  DEFAULT GETUTCDATE()    -- Zeitpunkt des letzten schreibenden Zugriffs
  , szUserModified          NVARCHAR(64)      NOT NULL  DEFAULT N''             -- letzte Änderung durchgeführt von

  CONSTRAINT PK_tblBsp_Tabelle PRIMARY KEY CLUSTERED 
  (
	  nKey ASC
  )WITH  FILLFACTOR = 100
  ) 
  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N'tblBsp_Tabelle')) BEGIN
    PRINT N'tblBsp_Tabelle : Tabelle wurde erfolgreich erstellt '
  END
  ELSE BEGIN
    PRINT N'tblBsp_Tabelle : Tabelle konnte nicht erstellt werden '
  END
END
ELSE BEGIN
  PRINT N'tblBsp_Tabelle : Tabelle existiert bereits '
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO
