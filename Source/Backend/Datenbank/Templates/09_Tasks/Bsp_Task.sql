SET QUOTED_IDENTIFIER OFF
GO

WHILE EXISTS (SELECT job_id FROM msdb.dbo.sysjobs WHERE (name = N'Bsp_Task')) BEGIN 
  EXEC msdb.dbo.sp_delete_job @job_name=N'Bsp_Task', @delete_unused_schedule=1
END
GO 

PRINT N'Taks Bsp_Task erstellen' 
GO 

/****************************************************************************

  Task      : Bsp_Task

  Aufgabe   : Erstellt den Task. Anzupassende Punkte (auser Name) ist mit ToDo gekennzeichnet

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)

****************************************************************************/



/****** Object:  Job [Bsp_Task]    Script Date: 24.04.2018 09:03:51 ******/
BEGIN TRANSACTION
DECLARE @ReturnCode INT = 0
DECLARE @szDbName SYSNAME = DB_NAME()

/****** Object:  JobCategory [Data Collector]    Script Date: 24.04.2018 09:03:52 ******/
IF NOT EXISTS (SELECT name FROM msdb.dbo.syscategories WHERE name=N'Data Collector' AND category_class=1)
BEGIN
EXEC @ReturnCode = msdb.dbo.sp_add_category @class=N'JOB', @type=N'LOCAL', @name=N'Data Collector'
IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback

END

DECLARE @jobId BINARY(16)
EXEC @ReturnCode =  msdb.dbo.sp_add_job @job_name=N'Bsp_Task',                        -- ToDo: Name muss eindeutig sein und darf kein Prozentzeichen ( % ) enthalten
		@enabled=1,                                                                       -- ToDo: Status (1 = aktiv, 0 = inaktiv)
		@notify_level_eventlog=0, 
		@notify_level_email=0, 
		@notify_level_netsend=0, 
		@notify_level_page=0, 
		@delete_level=0, 
		@description=N'Löscht alte Daten',                                                -- ToDo: Beschreibung des Tasks
		@category_name=N'Data Collector',                                                 -- ToDo: die Kategorie für den Auftrag. Categoryist vom Datentyp sysname und hat den Standardwert NULL
		@owner_login_name=N'sa', @job_id = @jobId OUTPUT                                  -- ToDo: Wenn nicht sa, dann Benutzer anpassen
IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback

/****** Object:  Step [ErstelleCSV]    Script Date: 24.04.2018 09:03:52 ******/
EXEC @ReturnCode = msdb.dbo.sp_add_jobstep @job_id=@jobId, @step_name=N'Löschen',     -- ToDo: Name des ersten Schrittes
		@step_id=1, 
		@cmdexec_success_code=0, 
		@on_success_action=1, 
		@on_success_step_id=0, 
		@on_fail_action=2, 
		@on_fail_step_id=0, 
		@retry_attempts=0, 
		@retry_interval=0, 
		@os_run_priority=0, @subsystem=N'TSQL', 
		@command=N'exec spBsp_MaintenancePlan @szUserName = ''Auto'' ',                   -- ToDo: Befehl, der beim ersten Schritt ausgeführt werden soll 
		@database_name=@szDbName, 
		@flags=0
IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback
EXEC @ReturnCode = msdb.dbo.sp_update_job @job_id = @jobId, @start_step_id = 1
IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback
EXEC @ReturnCode = msdb.dbo.sp_add_jobschedule @job_id=@jobId, @name=N'Daily',        -- ToDo: Name des Zeitplans
		@enabled=1,                                                                       -- ToDo: Status des Plans (1 = aktiv, 0 = inaktiv)
		@freq_type=4,                                                                     -- ToDo: Intervall 
                                                                                      --        1   = Einmal
                                                                                      --        4	  = Täglich
                                                                                      --        8	  = Wöchentlicher Zeitplan
                                                                                      --        16	= Monatlicher Zeitplan
                                                                                      --        32	= Monatlich, relativ zu frequency_interval.
                                                                                      --        64	= Ausführen, wenn der SQL Server-Agent-Dienst gestartet wird.
                                                                                      --        128 = Ausführen, wenn sich der Computer im Leerlauf befindet.
		@freq_interval=1,                                                                 -- ToDo: Tag, an dem der Auftrag ausgeführt wird, anhänig vom Typ @freq_type (Default = 0)
                                                                                      --          wird nicht verwendet bei Typ 1,64,128
                                                                                      --          @freq_type = 4 (Täglich)
                                                                                      --                        1 = Alle frequency_interval Tage
                                                                                      --          @freq_type = 8 (Wöchentlicher Zeitplan)
                                                                                      --                        1 = Sonntag
                                                                                      --                        2 = Montag
                                                                                      --                        4 = Dienstag
                                                                                      --                        8 = Mittwoch
                                                                                      --                        16 = Donnerstag
                                                                                      --                        32 = Freitag
                                                                                      --                        64 = Samstag
                                                                                      --          @freq_type = 16 (Monatlicher Zeitplan)
                                                                                      --                        1-31 = Am frequency_interval Tag des Monats
                                                                                      --          @freq_type = 32  (Monatlich, relativ)
                                                                                      --                        1 = Sonntag
                                                                                      --                        2 = Montag
                                                                                      --                        3 = Dienstag
                                                                                      --                        4 = Mittwoch
                                                                                      --                        5 = Donnerstag
                                                                                      --                        6 = Freitag
                                                                                      --                        7 = Samstag
                                                                                      --                        8 = Tag
                                                                                      --                        9 = Arbeitstag
                                                                                      --                        10 = Wochenendtag
		@freq_subday_type=1,                                                              -- ToDo: Einheit @freq_subday_interval
                                                                                      --        0x1	Zum angegebenen Zeitpunkt
                                                                                      --        0x4	Minuten
                                                                                      --        0x8	Stunden
		@freq_subday_interval=0,                                                          -- ToDo: Anzahl von Minuten/Stunden, wenn @freq_subday_type = 4 oder 8
		@freq_relative_interval=0,                                                        -- ToDo: Relaation, wenn @freq_type = 32  (Monatlich, relativ)
                                                                                      --                        1	= Erster
                                                                                      --                        2	= Zweimal
                                                                                      --                        4	= Dritter
                                                                                      --                        8	= Vierter
                                                                                      --                        16= Letzter

		@freq_recurrence_factor=0,                                                        -- ToDo: Anzahl der Wochen oder Monate zwischen der geplanten Ausführung (@freq_type = 8,16,32)
		@active_start_date=20180424,                                                      -- ToDo: Startdatum (YYYYMMDD)
		@active_end_date=99991231,                                                        -- ToDo: Enddatum (YYYYMMDD)
		@active_start_time=4242,                                                          -- ToDo: Uhrzeit, wann der Job laufen soll (HHMMSS)
		@active_end_time=235959,                                                          -- ToDo: Uhrzeit, wennn der Job beendet werden soll (HHMMSS)
		@schedule_uid=N'3e15e4d4-10c4-4c6f-9abf-49934cb90c75'                             -- ToDo: uniqueidentifier zur eindeutigen definiton des Zeitplanes
IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback
EXEC @ReturnCode = msdb.dbo.sp_add_jobserver @job_id = @jobId, @server_name = N'(local)'
IF (@@ERROR <> 0 OR @ReturnCode <> 0) GOTO QuitWithRollback
COMMIT TRANSACTION
GOTO EndSave
QuitWithRollback:
    IF (@@TRANCOUNT > 0) ROLLBACK TRANSACTION
EndSave:

GO


