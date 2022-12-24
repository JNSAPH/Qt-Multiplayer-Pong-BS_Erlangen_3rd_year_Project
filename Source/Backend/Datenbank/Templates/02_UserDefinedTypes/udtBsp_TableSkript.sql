
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

IF NOT EXISTS (SELECT * FROM sys.types WHERE is_user_defined = 1 AND name = N'udtBsp_TableSkript') BEGIN 
  PRINT 'udtBsp_TableSkript : Tabellentyp erstellen'
  
  CREATE TYPE udtBsp_TableSkript AS TABLE  
  (
  /****************************************************************************

    Typ       : udtBsp_TableSkript

    Aufgabe   : Legt einen User defined type in Form einer Tabelle an. 
                udtBsp_TableSkript ist dabei der Name des neuen Typs

    Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
                     
  ****************************************************************************/
  -- Tabellendefiniton
      nKey                  INT  
  )

  IF EXISTS (SELECT * FROM sys.types WHERE is_user_defined = 1 AND name = N'udtBsp_TableSkript') BEGIN
    PRINT N'udtBsp_TableSkript : Tabellentyp wurde erstellt'
  END ELSE BEGIN
    PRINT N'udtBsp_TableSkript : Tabellentyp konnte nicht erstellt werden'
  END
END ELSE BEGIN
  PRINT 'udtBsp_TableSkript : Tabellentyp existiert bereits'
END
GO
