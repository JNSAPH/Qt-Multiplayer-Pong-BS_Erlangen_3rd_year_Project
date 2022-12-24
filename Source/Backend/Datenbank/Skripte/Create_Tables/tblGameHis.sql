SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO


/****************************************************************************

  Tabelle   : tblGameHis

  Aufgabe   : Legt eine Tabelle mit dem Namen tblGameHis an

  Historie  : Datum   Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
              24.12.  DB      Erstellt

****************************************************************************/
PRINT N'tblGameHis : Tabelle erstellen '

IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N'tblGameHis')) BEGIN
  PRINT N'tblGameHis : Tabelle wird erstellt '

  CREATE TABLE dbo.tblGameHis(
  -- Schlüsselinformationen
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
    nKey                    BIGINT             NOT NULL  IDENTITY(1,1)           -- eindeutiger Schlüssel der Tabelle
       
  -- Nettodaten
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
  , nGame_Id                INT                NOT NULL  DEFAULT -1
  , nPlayer_Id              INT                NOT NULL  DEFAULT -1
  , szInput                 NVARCHAR(50)       NOT NULL  DEFAULT N''
   
  -- Verwaltungsinformationen
  -- --------------------------------------------------------------------------------
  -- --------------------------------------------------------------------------------
  , szComment               NVARCHAR(256)     NOT NULL  DEFAULT N''             -- Freiers Kommentarfeld
  , dtCreated               DATETIME2         NOT NULL  DEFAULT GETUTCDATE()    -- Zeitpunkt des Erstellens
  , szUserCreated           NVARCHAR(256)     NOT NULL  DEFAULT N''             -- Erstellt von
  , dtLastModified          DATETIME2         NOT NULL  DEFAULT GETUTCDATE()    -- Zeitpunkt des letzten schreibenden Zugriffs
  , szUserModified          NVARCHAR(64)      NOT NULL  DEFAULT N''             -- letzte Änderung durchgeführt von

  CONSTRAINT PK_tblGameHis PRIMARY KEY CLUSTERED 
  (
	  nKey ASC
  )WITH  FILLFACTOR = 100
  ) 
  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N'tblGameHis')) BEGIN
    PRINT N'tblGameHis : Tabelle wurde erfolgreich erstellt '
  END
  ELSE BEGIN
    PRINT N'tblGameHis : Tabelle konnte nicht erstellt werden '
  END
END
ELSE BEGIN
  PRINT N'tblGameHis : Tabelle existiert bereits '
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO
