
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

WHILE EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'trBsp_Tabelle_Insert')) 
  DROP TRIGGER trBsp_Tabelle_Insert 
GO 

/****************************************************************************

  Trigger   : trBsp_Tabelle_Insert
  
  Aufgabe   : Trigger der Auslöst, wenn in der tblBsp_Tabelle ein Eintrag hinzugefügt wird und diesen in die tblBsp_TabelleHistory schreibt
      
  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
              
****************************************************************************/
PRINT 'trBsp_Tabelle_Insert : Trigger erstellen '
   
IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = object_id('trBsp_Tabelle_Insert'))BEGIN
  Print 'trBsp_Tabelle_Insert : Trigger wird erstellt '
  
  EXECUTE
  ("
    CREATE TRIGGER trBsp_Tabelle_Insert
      ON  tblBsp_Tabelle
      AFTER INSERT  
    AS 
    BEGIN
      INSERT INTO tblBsp_TabelleHistory(nTabelleID, szBeispiel, szAction , szComment, dtLastModified, szUserModified )
      SELECT                            nKey      , szBeispiel, N'Insert', szComment, dtLastModified, szUserModified
      FROM INSERTED
    END 
  ")

  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('trBsp_Tabelle_Insert')) BEGIN
    PRINT 'trBsp_Tabelle_Insert : Trigger wurde erfolgreich erstellt '
  END
  ELSE BEGIN
    PRINT 'trBsp_Tabelle_Insert : Trigger konnte nicht erstellt werden '
  END
END
ELSE BEGIN
  PRINT 'trBsp_Tabelle_Insert : Trigger existiert bereits '
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

