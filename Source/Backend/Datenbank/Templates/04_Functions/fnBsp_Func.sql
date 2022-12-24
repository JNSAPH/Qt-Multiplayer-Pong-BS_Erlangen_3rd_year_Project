SET QUOTED_IDENTIFIER OFF 
GO

DROP FUNCTION IF EXISTS fnBsp_Func
GO

PRINT 'Funktion fnBsp_Func wird angelegt..'
GO

CREATE FUNCTION fnBsp_Func(
  -- -------------------------------------------------------------------------
  -- Funktionsparameter
  -- -------------------------------------------------------------------------
  @nId      INT             -- Parameterbeschreibung
) 
RETURNS DATETIME2
AS
/********************************************************************************

  Funktion  : fnBsp_Func

  Aufgabe   : Beschreibung der Funktion

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

********************************************************************************/
BEGIN

  RETURN N''

END
GO

-- Ausgabe
IF EXISTS (SELECT * FROM sysobjects WHERE id = OBJECT_ID(N'fnBsp_Func')) BEGIN
  PRINT N'fnBsp_Func : Funktion wurde erfolgreich erstellt'
END ELSE BEGIN
  PRINT N'fnBsp_Func : Funktion konnte nicht erstellt werden'
END

GO 
