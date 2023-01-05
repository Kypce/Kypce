CREATE TABLE Company(
  compNa VARCHAR(10) NOT NULL,
  compAdd VARCHAR(40),
  compSize INTEGER,
  PRIMARY KEY(compNa)
);

CREATE TABLE Department(
  deptCompany VARCHAR(10) NOT NULL,
  deptNa VARCHAR(10) NOT NULL,
  deptSize INTEGER,
  deptComments VARCHAR(20),
  PRIMARY KEY(deptCompany, deptNa),
  FOREIGN KEY(deptCompany) REFERENCES Company(compNa)
);

CREATE TABLE Contacts( 
  id VARCHAR(6) NOT NULL,
  Fname VARCHAR(15),
  Lname VARCHAR(15),
  gender VARCHAR(3),
  jobtitle VARCHAR(10),
  employer VARCHAR(10),
  team VARCHAR(10),
  homeAdd VARCHAR(40),
  mailAdd VARCHAR(40),
  comments VARCHAR(30),
  PRIMARY KEY(id),
  FOREIGN KEY(employer, team) REFERENCES Department(deptCompany, deptNa)
);

CREATE TABLE InteractionEvents( 
  contact VARCHAR(6) NOT NULL,
  intType VARCHAR(10) NOT NULL,
  intDate DATE NOT NULL,
  comments VARCHAR(20),
  PRIMARY KEY(contact, intType, intDate),
  FOREIGN KEY(contact) REFERENCES Contacts(id)
);

CREATE TABLE Manager( 
  manId VARCHAR(6) NOT NULL,
  manCo VARCHAR(10),
  manTeam VARCHAR(10),
  secretary VARCHAR(6),
  bonus DECIMAL(8,2),
  PRIMARY KEY(manId),
  FOREIGN KEY(manId) REFERENCES Contacts(id),
  FOREIGN KEY(manCo, manTeam) REFERENCES Department(deptCompany, deptNa),
  FOREIGN KEY(secretary) REFERENCES Contacts(id)
);

CREATE TABLE Communication( 
  commId VARCHAR(6) NOT NULL,
  homeNum VARCHAR(12),
  officeNum VARCHAR(12),
  cellNum VARCHAR(12),
  faxNum VARCHAR(12),
  email VARCHAR(16),
  PRIMARY KEY(commId),
  FOREIGN KEY(commId) REFERENCES Contacts(id)
);
