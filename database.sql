BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS `settings` (
	`name`	TEXT NOT NULL UNIQUE,
	`value`	INTEGER,
	PRIMARY KEY(`name`)
);
CREATE TABLE IF NOT EXISTS `photos` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`hash`	TEXT,
	`original_name`	TEXT,
	`import_date`	INTEGER,
	`import_time`	INTEGER,
	`exif_height`	INTEGER,
	`exif_width`	INTEGER,
	`exif_brand`	TEXT,
	`exif_peripheral`	TEXT,
	`fav`	INTEGER DEFAULT 0
);
CREATE TABLE IF NOT EXISTS `includes` (
	`including_folder`	INTEGER,
	`included_folder`	INTEGER,
	FOREIGN KEY(`included_folder`) REFERENCES `folders`(`id`),
	PRIMARY KEY(`including_folder`,`included_folder`),
	FOREIGN KEY(`including_folder`) REFERENCES `folders`(`id`)
);
CREATE TABLE IF NOT EXISTS `holds` (
	`holding_folder`	INTEGER,
	`holded_album`	INTEGER,
	FOREIGN KEY(`holded_album`) REFERENCES `albums`(`id`),
	FOREIGN KEY(`holding_folder`) REFERENCES `folders`(`id`),
	PRIMARY KEY(`holding_folder`,`holded_album`)
);
CREATE TABLE IF NOT EXISTS `folders` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`name`	INTEGER
);
CREATE TABLE IF NOT EXISTS `contains` (
	`containing_album`	INTEGER,
	`contained_photo`	INTEGER,
	FOREIGN KEY(`contained_photo`) REFERENCES `photos`(`id`),
	FOREIGN KEY(`containing_album`) REFERENCES `albums`(`id`),
	PRIMARY KEY(`containing_album`,`contained_photo`)
);
CREATE TABLE IF NOT EXISTS `albums` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`name`	TEXT
);
COMMIT;
