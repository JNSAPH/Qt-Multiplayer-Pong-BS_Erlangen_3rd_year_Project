SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM dbo.sysobjects WHERE id = OBJECT_ID(N'dbo.vwBsp_Tabelle') AND OBJECTPROPERTY(id, N'IsView') = 1)
  DROP VIEW dbo.vwBsp_Tabelle
GO

CREATE VIEW dbo.vwBsp_Tabelle
/****************************************************************************
  
  View      :  vwBsp_Tabelle

  Aufgabe   :  Legt eine View mit dem Namen vwBsp_Tabelle an Darin können verschiedene Tabellen zusammen gefügt (Join) werden 
       
  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
            
****************************************************************************/
AS

SELECT *
FROM tblBsp_Tabelle

GO
SET QUOTED_IDENTIFIER OFF 
GO
SET ANSI_NULLS ON 
GO

