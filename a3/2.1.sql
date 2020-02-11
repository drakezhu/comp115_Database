CREATE TABLE Department(
	`Department_Name` VARCHAR NOT NULL,
	`Address` VARCHAR NULL,
	`PhoneNumber` INT NULL,
	`Website` VARCHAR NULL,
	PRIMARY KEY(`Department_Name`)
)

CREATE TABLE Professor(
	`Professor_id` INT NOT NULL,
	`Email` VARCHAR NULL,
	`PhoneNumber` INT NULL,
	`Title` VARCHAR NULL,
	PRIMARY KEY(`Professor_id`)
)

CREATE TABLE Work(
	`Department_Name` VARCHAR NOT NULL,
	`Professor_id` VARCHAR NOT NULL references Professor,
	`ChairMan` VARCHAR NULL,
	PRIMARY KEY(`Department_Name`)
)


CREATE TABLE Course(
	`CatlogNumber` VARCHAR NOT NULL,
	`Prerequisite` VARCHAR NOT NULL references Course,
	`Department_Name` VARCHAR NOT NULL references Professor,
	`Description` VARCHAR NULL,
	PRIMARY KEY(`CatlogNumber`)
)

CREATE TABLE Offering(
	`CatlogNumber` VARCHAR NOT NULL,
	`Semester` VARCHAR NOT NULL,
	`Description` VARCHAR NOT NULL,
	`Professor_id` VARCHAR NOT NULL references Professor,
	`Student_id` VARCHAR NOT NULL references Student,
	`TA_id` VARCHAR NOT NULL references TA,
	PRIMARY KEY(`CatlogNumber`,`Semester`)
)

CREATE TABLE OfferProfessor(
	`CatlogNumber` VARCHAR NOT NULL,
	`Semester` VARCHAR NOT NULL,
	`Professor_id` VARCHAR NOT NULL,
	PRIMARY KEY(`CatlogNumber`,`Semester`, `Professor_id`)
)

CREATE TABLE Student(
	`Student_id` INT NOT NULL,
	`Name` VARCHAR NOT NULL,
	PRIMARY KEY(`Student_id`)
)

CREATE TABLE TA(
	`TA_id` VARCHAR NOT NULL,
	`Student_id` VARCHAR NOT NULL references Student,
	`CatlogNumber` VARCHAR NOT NULL references Course,
	`Semester` VARCHAR NOT NULL references Offering,
	PRIMARY KEY(`TA_id`)
)

CREATE TABLE TA_Offering(
	`TA_id` VARCHAR NOT NULL,
	`Semester` VARCHAR NOT NULL,
	`CatlogNumber` VARCHAR NOT NULL,
	PRIMARY KEY(`TA_id`,`CatlogNumber`,`Semester`)
)

CREATE TABLE TakeCourse(
	`CatlogNumber` VARCHAR NOT NULL,
	`Student_id` VARCHAR NOT NULL,
	PRIMARY KEY(`CatlogNumber`,`Student_id`)
)

CREATE TABLE Task(
	`Task_id` VARCHAR NOT NULL,
	`CatlogNumber` VARCHAR NOT NULL references Course,
	`Semester` VARCHAR NOT NULL references Offering,
	`Name` VARCHAR NOT NULL,
	`Weight` REAL NOT NULL,
	PRIMARY KEY(`Task_id`)
)

CREATE TABLE Grade(
	`Task_id` VARCHAR NOT NULL,
	`Student_id` VARCHAR NOT NULL,
	`Score` VARCHAR NOT NULL,
	PRIMARY KEY(`Task_id`,`Student_id`)
)

