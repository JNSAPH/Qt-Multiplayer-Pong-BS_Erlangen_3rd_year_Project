# Konzept für Projekt ITP

## Grundvoraussetzungen:

### Ein multiplayer online Spiel
- erster Wurf: SpaceInvaderz 1v1
- shooten, moven  
- evtl gegeneinander spaceinvaden? idk
  


### Game wird per Server gehostet
- httpServer via qt
- Effektiv als MVC realisiert
- Server hostet allen code


### in Browser spielbar
- browser als PlayerInput
- basically View 

### Datenbank zur Datenverwaltung nutzen
- model
- Datenhaltung 
- Datenbankanbindung ? 
- Historisierung
  

### Spielzüge historisieren
 - in Datenbank
 - genau genug, um KI anzufüttern
 - simpel enough, um nicht alles zu killen
 - 1 Eintrag per Tick
 - Snapshots/KeyStrokes 


## Weiterführende Dokus
- [Server](Server.md)
- [Kommunikation](Kommunikation.md)
- [GameLogic](GameLogic.md)
- [Datenbank](Datenbank.md)

  