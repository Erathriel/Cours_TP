drop table if exists article,client,distributeur;
-- ,commande,colis;

create table if not exists article(
	refArticle int(10) NOT NULL,
	stock int(10),
	PRIMARY KEY(refArticle)
) DEFAULT CHARSET=utf8;

create table if not exists client(
	refClient varchar(20) NOT NULL,
	PRIMARY KEY (refClient)
) DEFAULT CHARSET=utf8;

create table if not exists distributeur(
	refDistrib int(10) NOT NULL,
	PRIMARY KEY(refDistrib)
) DEFAULT CHARSET=utf8;

-- create table if not exists article(
--
-- ) DEFAULT CHARSET=utf8;

-- create table if not exists article(
--
-- ) DEFAULT CHARSET=utf8;

DESCRIBE article;
DESCRIBE client;
DESCRIBE distributeur;
