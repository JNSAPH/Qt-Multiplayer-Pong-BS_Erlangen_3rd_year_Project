
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

/********************************************************************************
  Defult    : defBsp_Now
              
  Aufgabe   : Default mit dem Namen defBsp_Now
             
  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

********************************************************************************/
  
IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'defBsp_Now'))
BEGIN

  PRINT N'Anlegen des Defaults defBsp_Now... '
  
  EXEC( '
    CREATE DEFAULT defBsp_Now AS SYSUTCDATETIME()  /* Defaultwert*/
	  ')
END
GO

