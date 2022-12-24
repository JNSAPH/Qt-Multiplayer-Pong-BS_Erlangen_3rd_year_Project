
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

WHILE EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'trBsp_Tabelle_Update')) 
  DROP TRIGGER trBsp_Tabelle_Update 
GO 

/****************************************************************************

  Trigger   : trBsp_Tabelle_Update
  
  Aufgabe   : Trigger der Auslöst, wenn in der tblBsp_Tabelle ein Eintrag geändert wird und diesen in die tblBsp_TabelleHistory schreibt
      
  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
              
****************************************************************************/
PRINT 'trBsp_Tabelle_Update : Trigger erstellen '
   
IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = object_id('trBsp_Tabelle_Update'))BEGIN
  Print 'trBsp_Tabelle_Update : Trigger wird erstellt '
  
  EXECUTE
  ("
    CREATE TRIGGER trBsp_Tabelle_Update
      ON  tblBsp_Tabelle
      AFTER UPDATE  
    AS 
    BEGIN
      INSERT INTO tblBsp_TabelleHistory(nTabelleID, szBeispiel, szAction , szComment, dtLastModified, szUserModified )
      SELECT                            nKey      , szBeispiel, N'Update', szComment, dtLastModified, szUserModified
      FROM INSERTED
    END 
  ")

  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('trBsp_Tabelle_Update')) BEGIN
    PRINT 'trBsp_Tabelle_Update : Trigger wurde erfolgreich erstellt '
  END
  ELSE BEGIN
    PRINT 'trBsp_Tabelle_Update : Trigger konnte nicht erstellt werden '
  END
END
ELSE BEGIN
  PRINT 'trBsp_Tabelle_Update : Trigger existiert bereits '
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

