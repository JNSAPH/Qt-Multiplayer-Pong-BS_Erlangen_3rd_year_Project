
PRINT ''
PRINT 'Die Tabelle tblBsp_Tabelle wird initialisiert...'
PRINT ''

SET NOCOUNT ON

/****************************************************************************

  Init      : Initialisieren der Tabelle tblBsp_Tabelle

  Aufgabe   : Legt Datensätze an

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

****************************************************************************/
DECLARE @dtInit DATETIME2 = GETUTCDATE()

DELETE FROM tblBsp_Tabelle

INSERT INTO tblBsp_Tabelle( szBeispiel, szComment , dtLastModified, szUserModified)
VALUES                    ( N'Data1'  , N''       , @dtInit       , N'INIT')
     ,                    ( N'Data2'  , N''       , @dtInit       , N'INIT')


GO 

