/****************************************************************************

  Datenbank : Skript zum anlegen einer Datenbank 

  Aufgabe   : Skript erstellt eine neue Datenbank
              dbDatenbankname durch den neuen Namen ersetzen

  Historie  : Datum  Kürzel  Tätigkeitsbeschreibung (zb Erstellt)
                     
****************************************************************************/

USE [master]
GO

IF DB_ID('dbDatenbankname') IS NOT NULL BEGIN
  PRINT 'dbDatenbankname : Datenbank existiert bereits'
	SET NOEXEC ON
END ELSE BEGIN
  PRINT 'dbDatenbankname : Datenbank erstellen'
END

CREATE DATABASE [dbDatenbankname]
CONTAINMENT = NONE
ON  PRIMARY 
( NAME = N'dbDatenbankname'
, FILENAME = N'C:\SEHOmes\40 SEHOmes\Database\dbDatenbankname.mdf' 
, SIZE = 8192KB 
, MAXSIZE = UNLIMITED
, FILEGROWTH = 65536KB )
LOG ON 
( NAME = N'dbDatenbankname_log'
, FILENAME = N'C:\SEHOmes\40 SEHOmes\Database\dbDatenbankname_log.ldf' 
, SIZE = 8192KB 
, MAXSIZE = 2048GB 
, FILEGROWTH = 65536KB )

IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled')) BEGIN
EXEC [dbDatenbankname].[dbo].[sp_fulltext_database] @action = 'enable'
END
GO
  
ALTER DATABASE [dbDatenbankname] SET ANSI_NULL_DEFAULT OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET ANSI_NULLS OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET ANSI_PADDING OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET ANSI_WARNINGS OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET ARITHABORT OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET AUTO_CLOSE OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET AUTO_SHRINK OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET AUTO_UPDATE_STATISTICS ON 
GO 
ALTER DATABASE [dbDatenbankname] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET CURSOR_DEFAULT  GLOBAL 
GO 
ALTER DATABASE [dbDatenbankname] SET CONCAT_NULL_YIELDS_NULL OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET NUMERIC_ROUNDABORT OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET QUOTED_IDENTIFIER OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET RECURSIVE_TRIGGERS OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET  DISABLE_BROKER 
GO 
ALTER DATABASE [dbDatenbankname] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET TRUSTWORTHY OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET PARAMETERIZATION SIMPLE 
GO 
ALTER DATABASE [dbDatenbankname] SET READ_COMMITTED_SNAPSHOT OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET HONOR_BROKER_PRIORITY OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET RECOVERY SIMPLE 
GO 
ALTER DATABASE [dbDatenbankname] SET  MULTI_USER 
GO 
ALTER DATABASE [dbDatenbankname] SET PAGE_VERIFY CHECKSUM  
GO 
ALTER DATABASE [dbDatenbankname] SET DB_CHAINING OFF 
GO 
ALTER DATABASE [dbDatenbankname] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [dbDatenbankname] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [dbDatenbankname] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [dbDatenbankname] SET  READ_WRITE
GO 

PRINT 'dbDatenbankname : Datenbank wurde erstellt'
GO

SET NOEXEC OFF

USE [dbDatenbankname]
GO
