
SET QUOTED_IDENTIFIER OFF
GO
SET ANSI_NULLS ON 
GO

/********************************************************************************
  Regel     : rulBsp_multiplyByTen
              
  Aufgabe   : Regel mit dem Namen rulBsp_multiplyByTen
             
  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

********************************************************************************/
  
IF NOT EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'rulBsp_multiplyByTen'))
BEGIN

  PRINT N'Anlegen der Regel rulBsp_multiplyByTen... '

  EXEC( '
    CREATE RULE rulBsp_MultiplyByTen
    AS @Var % 10 = 0
    AND @Var > 100
    AND @vVar < 999
	  ')
END
GO

