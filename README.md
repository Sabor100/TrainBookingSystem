# Tågbokningssystem

## Projektbeskrivning
Systemet är skapat för att hantera bokning av tågresor för passagerare med stöd för att hantera flera klasser (första och andra klass), tågdetaljer och biljetthantering.

### Funktionalitet

#### Biljetthantering
- Skapar biljetter för passagerare.
- Hämtar detaljer om en specifik biljett.
- Raderar biljetter.

#### Passagerarhantering
- Registrerar passagerarinformation (namn, personnummer, sittplatsnummer).
- Hanterar passagerartyp (första klass eller andra klass) och tillhörande förmåner.

#### Tåghantering
- Hanterar information om tåg såsom destination sort, kapacitet och tågnummer.
- Visar antal tillgängliga tåg.

#### Systemfunktioner
- Bokar biljett med ett tågnummer och förmåner såsom 1 eller 2 klass.
- Sparar och läser data (visar alla bokade biljetter).
- Söker efter passagerare baserat på namn.
- Raderar alla bokningar.

### Klassfunktionalitet

- **Första klass:** Frukostalternativ (valbar) och sätestyp.  
- **Andra klass:** Bagageutrymme och måltid (ej valbar kost).

### Class: Passenger
**Egenskaper:**
- `name`: Namnet på passageraren.  
- `ssn`: Unikt personnummer för identifiering.  
- `seatNumber`: Tilldelad sittplats i tåget.

### Class: Ticket
**Egenskaper:**
- `ticketNr`: Biljettens ID.  
- `passenger`: Pekare till en passagerare.  
- `train`: Referens till det bokade tåget.

### Class: Train
**Egenskaper:**
- `trainNr`: Unikt tågnummer.  
- `destination`: Tågets destinationsort.

### Class: TrainCarage
**Egenskaper:**
- Antal tågvagnar och sittplatser.  
- Kapacitet för antal sittplatser i varje vagn.  
- Visar tillgängliga platser för passagerare att boka.

### Class: System
**Egenskaper:**
- `tickets`: Lista över alla biljetter.  
- `trains`: Lista över alla tåg.
