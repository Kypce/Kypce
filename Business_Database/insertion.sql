INSERT INTO Company VALUES('ABC Inc.', '1234 Izzy Lane, Tampa FL', 50);
INSERT INTO Company VALUES('XYZ Co.', '9876 Arcanine Rd, New York NY', 100);
INSERT INTO Company VALUES('Arcadia', '6363 Bungie Blvd, Seattle WA', 777);

INSERT INTO Department VALUES('ABC Inc.', 'Sales', 5, 'N/A');
INSERT INTO Department VALUES('ABC Inc.', 'DEF', 3, 'GHIJ ya know');
INSERT INTO Department VALUES('XYZ Co.', 'East', 19, 'N/A');
INSERT INTO Department VALUES('Arcadia', 'Sales', 57, 'Conduct sales');
INSERT INTO Department VALUES('Arcadia', 'Suros', 63, 'Just suros things');
INSERT INTO Department VALUES('Arcadia', 'Secretary', 22, 'N/A');
INSERT INTO Department VALUES('ABC Inc.', 'Secretary', 33, 'N/A');

INSERT INTO Contacts VALUES('JC1234', 'Josh', 'Class', 'M', 'Associate', 'Arcadia', 'Suros', '5678 Sagerk Rd, Seattle WA', '5678 Sagerk Rd, Seattle WA', 'Absolute G');
INSERT INTO Contacts VALUES('NC0112', 'Nick', 'Cherry', 'M', 'Associate', 'ABC Inc.', 'Sales', '3018 Trost Lane, Tampa FL', '3018 Trost Lane, Tampa FL', 'mad cause bad');
INSERT INTO Contacts VALUES('MC6363', 'Melissa', 'Class', 'F', 'Supervisor', 'ABC Inc.', 'DEF', '7503 Southwest Blvd, Tampa FL', '7503 Southwest Blvd, Tampa FL', 'Number 1');
INSERT INTO Contacts VALUES('JI8275', 'Josh', 'Ingeneri', 'M', 'Associate', 'XYZ Co.', 'East', '0029 Squirtle Lane, New York NY', '0029 Squirtle Lane, New York NY', 'Bassoon whisperer');
INSERT INTO Contacts VALUES('CL5678', 'Celia', 'Leto', 'F', 'Manager', 'Arcadia', 'Suros', '0112 Sherman Rd, Seattle WA', '0112 Sherman Rd, Seattle WA', 'Fish are friends not food');
INSERT INTO Contacts VALUES('JD5279', 'Jane', 'Doe', 'N/A', 'Secretary', 'Arcadia', 'Secretary', '7766 Chest St, Seattle WA', '9984 Pinefield Rd, Seattle WA', 'N/A');
INSERT INTO Contacts VALUES('MR3636', 'Matthew', 'Class', 'M', 'Secretary', 'ABC Inc.', 'Secretary', '2213 Wallaby Blvd, Tampa FL', '2213 Wallaby Blvd, Tampa FL', ':D');

INSERT INTO InteractionEvents VALUES('JC1234', 'Email', TO_DATE('12-01-2021', 'DD-MM-YYYY'), 'N/A');
INSERT INTO InteractionEvents VALUES('NC0112', 'Call', TO_DATE('22-12-2022', 'DD-MM-YYYY'), 'call back');
INSERT INTO InteractionEvents VALUES('NC0112', 'Mail', TO_DATE('22-03-2022', 'DD-MM-YYYY'), 'waiting for response');
INSERT INTO InteractionEvents VALUES('NC0112', 'Email', TO_DATE('12-09-2022', 'DD-MM-YYYY'), 'N/A');
INSERT INTO InteractionEvents VALUES('NC0112', 'Call', TO_DATE('17-04-2011', 'DD-MM-YYYY'), 'call back');
INSERT INTO InteractionEvents VALUES('JI8275', 'Email', TO_DATE('01-01-2011', 'DD-MM-YYYY'), 'N/A');
INSERT INTO InteractionEvents VALUES('CL5678', 'Call', TO_DATE('27-09-2001', 'DD-MM-YYYY'), 'successful');

INSERT INTO Manager VALUES('CL5678', 'Arcadia', 'Suros', 'JD5279', 10000.06);
INSERT INTO Manager VALUES('MC6363', 'ABC Inc.', 'DEF', 'MR3636', 11200.63);

INSERT INTO Communication VALUES('JC1234', '123-456-7890', '098-765-4321', '135-792-4680', '246-891-3570', 'jc1234@gmail.com');
INSERT INTO Communication VALUES('NC0112', '113-224-5566', '224-113-6655', '998-667-0909', '667-998-9090', 'nc0112@gmail.com');
INSERT INTO Communication VALUES('MC6363', '556-776-3214', '776-556-1432', '299-100-7373', '100-299-3737', 'mc6363@gmail.com');
INSERT INTO Communication VALUES('JI8275', '888-333-4444', '333-888-2222', '444-999-1111', '999-444-0001', 'ji8275@gmail.com');
INSERT INTO Communication VALUES('CL5678', '112-112-0112', '113-113-0113', '636-301-1269', '455-656-9301', 'cl5678@gmail.com');
INSERT INTO Communication VALUES('JD5279', '982-721-4201', '171-104-3186', '080-108-1485', '169-520-707', 'jd5279@gmail.com');
INSERT INTO Communication VALUES('MR3636', '493-190-1535', '050-122-1130', '450-023-6472', '836-785-2035', 'mr3636@gmail.com');
