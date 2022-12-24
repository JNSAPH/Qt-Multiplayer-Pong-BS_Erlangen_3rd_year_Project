
PRINT ''
PRINT 'Die Tabelle tblGameHis wird initialisiert...'
PRINT ''

SET NOCOUNT ON

/****************************************************************************

  Init      : Initialisieren der Tabelle tblGameHis   (WICHTIG!!!)
                                                      NUR FÜR TESTZWECKE
                                                      macht keinen sinn ne historie zu initialisieren lol

  Aufgabe   : Legt Datensätze an

  Historie  : Datum   Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
              24.12.  DB      Erstellt

****************************************************************************/
DECLARE @dtInit DATETIME2 = GETUTCDATE()

DELETE FROM tblGameHis

INSERT INTO tblGameHis( nGame_Id, nPlayer_Id, szInput, szComment , dtLastModified, szUserModified)
VALUES                    ( 1  , 1, N'Nach Hoch'        , @dtInit       , N'INIT')
     ,                    ( 1  , 2, N'Nach Links'       , @dtInit       , N'INIT')
     ,                    ( 1  , 1, N'Schießen'         , @dtInit       , N'INIT')
     ,                    ( 1  , 2, N'Nach Hoch'        , @dtInit       , N'INIT')
     ,                    ( 1  , 1, N'Schießen'         , @dtInit       , N'INIT')
     ,                    ( 1  , 2, N'Sterben'          , @dtInit       , N'INIT')




GO 

