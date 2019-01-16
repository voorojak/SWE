# CocktailPro Legacy

Im Jahr 2015 wurde eine Software zur Simulation eines Cocktail-Misch-Geräts entwickelt: der "CocktailPro". Die Software wurde aber nicht für einen dauerhaften Betrieb entwickelt. Deshalb enthält der Code praktisch keine Kommentare und leider auch keine andere Dokumentation. Auch kleinere Fehler sind bekannt, wurden aber nie korrigiert.
Nun soll die Software von Ihnen weiterentwickelt werden, allerdings so, dass die üblichen Qualitätsansprüche an eine "ernst gemeinte" Software erfüllt sind. 
Sie erhalten den vollständigen und kompilierbaren Code des CocktailPro's. 
Ihre Aufgabe im gesamten Praktikum besteht darin, das System wartbarer zu machen und um neue Funktionen zu erweitern. 


## Legen Sie los!

Um das Projekt weiterentwickeln und Tests erstellen zu können, müssen Sie das Projektverzeichnis auf Ihren lokalen Rechner "clonen". Falls die erforderliche Software bereits installiert ist, können Sie mit folgenden Befehlen den Code und die Tests erstellen.
- make build
- make build-tests

Wenn der Build erfolgreich verlaufen ist, finden Sie im Ordner "bin" die ausführbaren Konsolenanwendungen "CocktailPro.exe" und "CocktailProTest.exe".

### Voraussetzungen

In diesem Projekt verwenden wir Jenkins als Continuous Integration Server.
Innerhalb des Hochschulnetzwerks können Sie den Jenkins-Server einfach aufrufen. Von außerhalb der Hochschule müssen Sie eine VPN-Verbindung verwenden. Jenkins lädt Ihre Quellcode-Dateien automatisch aus Ihrem Git-Repository.
Die Entwicklung des Codes erfolgt unter Verwendung von Git.

Um die Software weiterentwickeln zu können, brauchen Sie entsprechende Software. Auf den Laborrechnern ist diese vorhanden, auf Ihrem Privatrechner müssen Sie die Software eventuell noch installieren
-	**Git** (https://git-scm.com) und 
-	evtl. ein **grafischer Git-Client** (z.B. https://tortoisegit.org/)
-	**VPN-Software** (z.B. https://github.com/openconnect/openconnect-gui/releases)  
	Als Gateway müssen Sie https://firewall.fbi.h-da.de eintragen, als Protokoll Cisco Anyconnect und als Usernamen Ihren ist-Account
-	**Gnu-Compiler g++** und **make** (Für Windows Cygwin: https://www.cygwin.com/)
-	**NetBeans für C++** (https://netbeans.org/features/cpp/)
-	**GoogleTest** https://github.com/google/googletest/releases/tag/release-1.8.0  
	muss als Bibliothek kompiliert und später eingebunden werden. Verwenden Sie dazu unbedingt die gleiche IDE wie für Ihr eigentliches Projekt. 


## Entwicklung in der lokalen IDE

Unm das Projekt in Ihrer IDE weiterzuentwickeln können Sie entweder 
1) das Makefile importieren  
Dann müssen Sie beim Build entsprechende Targets auswählen, um zwischen normalem Projekt und Test umzuschalten. Falls Sie spezielle Einstellungen brauchen, legen Sie im Makefile ein neues (!!) Target mit den gewünschten Einstellungen an. Verändern Sie aber keinesfalls die existierenden Einstellungen!
2) oder ein neues Projekt für eine Konsolenanwendung aufsetzen  
	Dann müssen Sie alle Quellcode-Dateien in das Projekt einfügen und zusätzlich noch aus dem Verzeichnis "main" - entweder die Datei main.cpp für das normale Projekt oder Main_TestAll.cpp für den Test mit GoogleTest.

### Viel Erfolg mit dem CocktailPro!

Ralf Hahn
