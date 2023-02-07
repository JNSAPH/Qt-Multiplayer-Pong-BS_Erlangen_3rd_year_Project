  
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

IF NOT EXISTS (SELECT * FROM sys.types WHERE is_user_defined = 1 AND name = N'udtBsp_SingleSkript') BEGIN 
  PRINT 'udtBsp_SingleSkript : Benutzertyp erstellen'
  
  CREATE TYPE dbo.udtBsp_SingleSkript FROM DATETIME2 NOT NULL 

  /********************************************************************************
    UDT       : udtBsp_SingleSkript
    
    Aufgabe   : Legt einen User defined type in Form einer Tabelle an. 
                udtBsp_SingleSkript ist dabei der Name des neuen Typs

    Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
    
  ********************************************************************************/
    
  /** Default dem Benutzerdatentyp zuordnen .. **/
  EXEC sp_bindefault 'defBsp_Now', 'udtBsp_SingleSkript'

  EXEC sp_bindrule 'rulBsp_multiplyByTen', 'udtBsp_SingleSkript'

END
GO

