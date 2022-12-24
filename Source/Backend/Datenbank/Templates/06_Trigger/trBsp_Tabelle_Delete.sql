
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

WHILE EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'trBsp_Tabelle_Delete')) 
  DROP TRIGGER trBsp_Tabelle_Delete 
GO 

/****************************************************************************

  Trigger   : trBsp_Tabelle_Delete
  
  Aufgabe   : Trigger der Auslöst, wenn in der tblBsp_Tabelle ein Eintrag gelöscht wird und diesen in die tblBsp_TabelleHistory schreibt
      
  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

****************************************************************************/
PRINT 'trBsp_Tabelle_Delete : Trigger erstellen '
   
IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = object_id('trBsp_Tabelle_Delete'))BEGIN
  Print 'trBsp_Tabelle_Delete : Trigger wird erstellt '
  
  EXECUTE
  ("
    CREATE TRIGGER trBsp_Tabelle_Delete
      ON  tblBsp_Tabelle
      AFTER DELETE  
    AS 
    BEGIN          
      INSERT INTO tblBsp_TabelleHistory(nTabelleID, szBeispiel, szAction , szComment, dtLastModified, szUserModified )
      SELECT                            nKey      , szBeispiel,  N'Delete', szComment, dtLastModified, szUserModified
      FROM DELETED 

    END 
  ")

  -- Ausgabe
  IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id('trBsp_Tabelle_Delete')) BEGIN
    PRINT 'trBsp_Tabelle_Delete : Trigger wurde erfolgreich erstellt '
  END
  ELSE BEGIN
    PRINT 'trBsp_Tabelle_Delete : Trigger konnte nicht erstellt werden '
  END
END
ELSE BEGIN
  PRINT 'trBsp_Tabelle_Delete : Trigger existiert bereits '
END

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

