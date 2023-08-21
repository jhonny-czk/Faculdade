/*--------------------------------------------------------------------------------*/
/*                 Banco de Dados Avançado: Estudo Dirigido 01                    */
/*                Lista de exercícios SQL (Microsoft Sql Server)                  */
/*  Advanced Database. List of SQL exercises (Sql Server)for college assignment.  */
/*--------------------------------------------------------------------------------*/


-- Create
-- Cria a Base de dados dos projeto DeliveryFood 
use aula;
go

create table Continente (
	Con_id 			int constraint PK_Continente primary key,
	Con_Nome 		varchar(50) not null,
	Con_Sigla  		varchar(05) not null
);

create table Pais (
	Pais_id 		int constraint PK_Pais primary key,
	Pais_Nome 		varchar(100),
	Pais_Oficial	varchar(100),
	Pais_Sigla1 	varchar(10),
	Pais_Sigla2 	varchar(10),
	Con_id 			int not null
	constraint  	FK_Pais_Continente foreign key (Con_id) references Continente(Con_id) 
);

create table Regiao (
	Reg_id 			int constraint PK_Regiao primary key,
	Reg_Nome 		varchar(50) not null,
	Reg_Sigla  		varchar(10) not null,
	Pais_id 		int not null,
	constraint  	FK_Regiao_Pais foreign key (Pais_id) references Pais(Pais_id) 
);

create table Estado (
	est_id 			int constraint PK_Estado primary key,
	est_Nome 		varchar(80) not null,
	est_Sigla  		varchar(02) not null,
	Pais_id 		int not null,
	Reg_id 			int not null,
	constraint  	FK_Estado_Regiao  foreign key (Reg_id)  references Regiao(Reg_id), 
	constraint  	FK_Estado_Pais	  foreign key (Pais_id) references Pais(Pais_id) 
);

create table CidadeTipo(
	ctp_id			int not null constraint PK_TipoCidade primary key,
	ctp_Descricao	varchar(50) not null
)

create table Cidade (
	cid_id			int not null constraint PK_Cidade primary key,
	cid_Nome		varchar(150) not null,
	ctp_id  		int null,
	est_id  		int not null,
	constraint  	FK_Cidade_CidadeTipo foreign key (ctp_id) references CidadeTipo(ctp_id), 
	constraint  	FK_Cidade_Estado foreign key (est_id) references Estado(est_id) 
);

create table Bairro (
	bai_id  		int not null identity(1,1) primary key,
	bai_Descricao 	varchar(100),
	cid_id  		int,
	constraint 		fk_Bairro_Cidade foreign key (cid_id) references cidade(cid_id)
);

create table Endereco (
	end_id			int not null identity (1,1) primary key,
	end_cep			char(09),
	end_descricao	varchar(100),
	bai_id  		int not null,
	constraint  	FK_Endereco_bairro foreign key (bai_id) references Bairro(bai_id) 
);

create table EstadoCivil (
	eci_id 			int not null identity (1,1) primary key,
	eci_nome 		varchar(100)
)

create table Genero (
	gen_id			int not null primary key,
	gen_descricao	varchar(30) not null 
);

create table Cliente (
	cli_id 			int not null identity(1,1) primary key,
	cli_nome 		varchar(100),
	cli_nascimento 	date,
	gen_id 			int not null,
	eci_id			int,
	end_id 			int,
	constraint 		FK_cliente_genero foreign key(gen_id) references Genero(gen_id),
	constraint 		fk_cliente_estadoCivil foreign key (eci_id) references estadoCivil(eci_id),
	constraint 		fk_cliente_endereco foreign key (end_id) references endereco(end_id)
);

create table Entregador (
	ent_id 			int not null identity(1,1) primary key,
	ent_nome 		varchar(100),
	ent_nascimento	date,
	ent_CNH			varchar(15),
	ent_CNH_Validade date,
	gen_id 			int not null,
	eci_id			int,
	end_id 			int,
	constraint 		FK_entregador_genero foreign key(gen_id) references Genero(gen_id),
	constraint 		fk_entregador_estadoCivil foreign key (eci_id) references estadoCivil(eci_id),
	constraint 		fk_entregador_endereco foreign key (end_id) references endereco(end_id)
);

create table cotacao (
	cot_campo char(60)
);

create table Loja (
	loj_id 			int not null identity(1,1) primary key,
	loj_nome 		varchar(100),
	end_id 			int,
	constraint 		fk_loja_endereco foreign key (end_id) references endereco(end_id)
);

create table CategoriaProduto (
	cat_id 			int not null identity(1,1) primary key,
	cat_descricao 	varchar(100)
);

create table Produto (
	pro_id 			int not null identity(1,1) primary key,
	pro_descricao 	varchar(100),
	pro_preco 		decimal(10,2),
	cat_id 			int,
	loj_id 			int,
	constraint 		fk_produto_categoria foreign key (cat_id) references CategoriaProduto(cat_id),
	constraint 		fk_produto_loja foreign key (loj_id) references loja(loj_id)
);

create table FormaPagamento (
	fpg_id 	  		int not null identity(1,1) primary key,
	fpg_descricao  	varchar(100)
);

create table Pedido (
	ped_id			int not null identity(1,1) primary key,
	ped_data 	    date,
	ped_status		int, -- 0-(Em Processamento), 1-(Em aberto), 2-(Cancelado). 3-(Entregue) 
	loj_id 			int,
	cli_id 			int,
	ent_id 			int,
	fpg_id 			int,
	constraint 		fk_pedido_loja foreign key (loj_id) references loja(loj_id),
	constraint 		fk_pedido_cliente foreign key (cli_id) references Cliente(cli_id),
	constraint 		fk_pedido_entregador foreign key (ent_id) references Entregador(ent_id),
	constraint 		fk_pedido_FormaPagamento foreign key (fpg_id) references FormaPagamento(fpg_id)
);

create table PedidoProduto (
	pdd_id 			int not null identity(1,1) primary key,
	ped_id 			int not null,
	pro_id 			int not null,
	ped_quantidade 	int,
	pro_preco 		decimal(10,2),
	constraint 		fk_pedidoProduto_pedido foreign key (ped_id) references pedido(ped_id),
	constraint 		fk_pedidoProduto_produto foreign key (pro_id) references produto(pro_id)
);


-- Insert
-- Insere os dados na base de dados DeliveryFood 
use aula;
go
set language brazilian;

-- Insere os dados na tabela Continente
insert into Continente (Con_id,	Con_Nome, Con_Sigla) values (1, 'África', 'AFR');
insert into Continente (Con_id,	Con_Nome, Con_Sigla) values (2, 'Antártida', 'ANT');
insert into Continente (Con_id,	Con_Nome, Con_Sigla) values (3, 'Ásia', 'ASI');
insert into Continente (Con_id,	Con_Nome, Con_Sigla) values (4, 'Europa', 'EUR');
insert into Continente (Con_id,	Con_Nome, Con_Sigla) values (5, 'América do Norte e Central', 'AME');
insert into Continente (Con_id,	Con_Nome, Con_Sigla) values (6, 'Oceania', 'OCE');
insert into Continente (Con_id,	Con_Nome, Con_Sigla) values (7, 'América do Sul', 'AMS');

-- Insere os dados na tabela Pais
insert into pais (Pais_id, con_id, Pais_Sigla1, Pais_Sigla2, Pais_Oficial, Pais_Nome) values (76,7,'BR','BRA','Federative Republic of Brazil','Rep??ca Federativa do Brasil');

-- Insere os dados na tabela de Regiões
insert into Regiao values (1, 'Sul', 'SU', 76);
insert into Regiao values (2, 'Centro-Oeste', 'CO', 76);
insert into Regiao values (3, 'Sudeste', 'SD', 76);
insert into Regiao values (4, 'Nordeste', 'ND', 76);
insert into Regiao values (5, 'Norte', 'NO', 76);

-- Insere os dados na tabela Estado
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (1, 'Acre', 'AC', 76, 5);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (2, 'Alagoas', 'AL', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (3, 'Amazonas', 'AM', 76, 5);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (4, 'Amapá', 'AP', 76, 5);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (5, 'Bahia', 'BA', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (6, 'Ceará', 'CE', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (7, 'Distrito Federal', 'DF', 76, 2);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (8, 'Espírito Santo', 'ES', 76, 3);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (9, 'Goiás', 'GO', 76, 2);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (10, 'Maranhão', 'MA', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (11, 'Minas Gerais', 'MG', 76, 3);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (12, 'Mato Grosso do Sul', 'MS', 76, 2);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (13, 'Mato Grosso', 'MT', 76, 2);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (14, 'Pará', 'PA', 76, 5);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (15, 'Paraíba', 'PB', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (16, 'Pernambuco', 'PE', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (17, 'Piauí', 'PI', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (18, 'Paraná', 'PR', 76, 1);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (19, 'Rio de Janeiro', 'RJ', 76, 3);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (20, 'Rio Grande do Norte', 'RN', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (21, 'Rondônia', 'RO', 76, 5);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (22, 'Roraima', 'RR', 76, 5);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (23, 'Rio Grande do Sul', 'RS', 76, 1);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (24, 'Santa Catarina', 'SC', 76, 1);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (25, 'Sergipe', 'SE', 76, 4);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (26, 'São Paulo', 'SP', 76, 3);
insert into estado (est_ID, est_Nome, est_Sigla, Pais_id, reg_id) values (27, 'Tocantins', 'TO', 76, 5);

-- Insere os dados na tabela Tipo de Cidade
insert into CidadeTipo values (1, 'Capital');
insert into CidadeTipo values (2, 'Região Metropolitana');
insert into CidadeTipo values (3, 'Interior');

-- Insere os dados na tabela Cidade
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (4174, 'Porto Alegre', 1, 23);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (4500, 'Florianópolis', 1, 24);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (2878, 'Curitiba', 1, 18);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (5270, 'São Paulo', 1, 26);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (1630, 'Belo Horizonte', 1, 11);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (3658, 'Rio de Janeiro', 1, 19);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (78, 'Vitória', 1, 8);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (3315, 'Recife', 1, 16);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (616, 'Salvador', 1, 5);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (756, 'Fortaleza', 1, 6);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (3770, 'Natal', 1, 20);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (4411, 'São Luiz', 3, 22);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (147, 'Maceió', 1, 2);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (3582, 'Teresina', 1, 17);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (5353, 'Aracaju', 1, 25);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (2655, 'João Pessoa', 1, 15);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (108, 'Belém', 1, 2);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (209, 'Macapá', 1, 4);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (94, 'Rio Branco', 1, 1);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (256, 'Manaus', 1, 3);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (4382, 'Porto Velho', 1, 21);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (2590, 'Boa Vista', 1, 15);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (882, 'Brasília', 1, 7);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (977, 'Goiânia', 1, 9);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (1383, 'Cuiabá', 1, 13);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (116, 'Campo Grande', 1, 12);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (3032, 'Palmas', 1, 18);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (3879, 'Bagé', 3, 23);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (1218, 'Imperatriz', 3, 10);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (4699, 'Videira', 3, 24);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (2976, 'Londrina', 3, 18);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (3518, 'Parnaíba', 3, 17);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (2389, 'Uberlândia', 3, 11);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (1455, 'Rondonópolis', 3, 13);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (4814, 'Campinas', 3, 26);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (2388, 'Uberaba', 3, 11);
insert into cidade (cid_id, cid_nome,ctp_id, est_id) values (4031, 'Gramado', 3, 23);

-- Porto Alegre
insert into bairro values ('Centro', 4174);
insert into bairro values ('Santana', 4174);
insert into bairro values ('Bonfim', 4174);
insert into bairro values ('Petropolis', 4174);

-- Florianópolis
insert into bairro values ('Centro', 4500);
insert into bairro values ('Campeche', 4500);
insert into bairro values ('Coqueiros', 4500);
insert into bairro values ('Agronomica', 4500);
insert into bairro values ('Jurere', 4500);
insert into bairro values ('Lagoa da conceicao', 4500);

-- Curitiba
insert into bairro values ('Centro', 2878);
insert into bairro values ('Kajuru', 2878);
insert into bairro values ('CIC', 2878);
insert into bairro values ('Agua verde', 2878);
insert into bairro values ('Atuba', 2878);
insert into bairro values ('Barigui', 2878);
insert into bairro values ('Seminario', 2878);
insert into bairro values ('Bacacheri', 2878);

-- São paulo
insert into bairro values ('Centro', 5270);
insert into bairro values ('Itaquera', 5270);
insert into bairro values ('Morumbi', 5270);
insert into bairro values ('Bexiga', 5270);
insert into bairro values ('Alphaville', 5270);
insert into bairro values ('Ibirapuera', 5270);
insert into bairro values ('Mooca', 5270);

-- Rio de Janeiro
insert into bairro values ('Centro', 3658);
insert into bairro values ('Ipanema', 3658);
insert into bairro values ('Barra da tijuca', 3658);
insert into bairro values ('Boa vista', 3658);
insert into bairro values ('Copacabana', 3658);
insert into bairro values ('Botafogo', 3658);
insert into bairro values ('Leblon', 3658);

-- Belo Horizonte
insert into bairro values ('Centro', 1630);
insert into bairro values ('Savassi', 1630);
insert into bairro values ('Pampulha', 1630);
insert into bairro values ('Lourdes', 1630);
insert into bairro values ('Cidade Nova', 1630);
insert into bairro values ('Belvedere', 1630);

-- Vitória
insert into bairro values ('Centro', 78);
insert into bairro values ('Itararé', 78);
insert into bairro values ('Caratoíra', 78);
insert into bairro values ('Bela vista', 78);

-- Recife
insert into bairro values ('Centro', 3315);
insert into bairro values ('Boa Viagem', 3315);
insert into bairro values ('Coqueiral', 3315);

-- Salvador
insert into bairro values ('Centro', 616);
insert into bairro values ('Ondina', 616);

-- Fortaleza
insert into bairro values ('Centro', 756);
insert into bairro values ('Guararapes', 756);
insert into bairro values ('Meireles', 756);

-- Demais cidades
insert into bairro values ('Centro', 3770);
insert into bairro values ('Centro', 4411);
insert into bairro values ('Centro', 147);
insert into bairro values ('Centro', 3582);
insert into bairro values ('Centro', 5353);
insert into bairro values ('Centro', 2655);
insert into bairro values ('Centro', 108);
insert into bairro values ('Centro', 209);
insert into bairro values ('Centro', 94);
insert into bairro values ('Centro', 256);
insert into bairro values ('Centro', 4382);
insert into bairro values ('Centro', 2590);
insert into bairro values ('Centro', 882);
insert into bairro values ('Centro', 977);
insert into bairro values ('Centro', 1383);
insert into bairro values ('Centro', 116);
insert into bairro values ('Centro', 3032);
insert into bairro values ('Centro', 3879);
insert into bairro values ('Centro', 1218);
insert into bairro values ('Centro', 4699);
insert into bairro values ('Centro', 2976);
insert into bairro values ('Centro', 3518);
insert into bairro values ('Centro', 2389);
insert into bairro values ('Centro', 1455);
insert into bairro values ('Centro', 4814);
insert into bairro values ('Centro', 2388);
insert into bairro values ('Centro', 4031);
insert into bairro values ('Centro', 1455);
insert into bairro values ('Centro', 4814);
insert into bairro values ('Centro', 2388);
insert into bairro values ('Centro', 4031);

-- Insere dados na tabela endereco
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 (NULL,'Avenida Afonso Pena, 76',4),
	 (NULL,'Avenida Alfredo Balena, 890',6),
	 (NULL,'Avenida Amazonas, 32',2),
	 (NULL,'Avenida Dos Andradas, 9',3),
	 (NULL,'Avenida Presidente Getúlio Vargas, 985',5),
	 (NULL,'Rua dos Caetes, 132',3),
	 (NULL,'Avenida Guarapuava, 1231',6),
	 (NULL,'Avenida Presidente Getúlio Vargas, 1431',7),
	 (NULL,'Avenida Sete de setembro, 3232',4),
	 (NULL,'Avenida Silva jardim, 654',6);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 ('80420-000','R. Comendador Araújo, 152',5),
	 (NULL,'Rua Emiliano Perneta, 34',5),
	 ('80420-000','Rua sete de setembro, 154',3),
	 (NULL,'Avenida boa viagem, 100',2),
	 (NULL,'Avenida Presidente Getúlio Vargas, 654',2),
	 (NULL,'Rua Caxangá, 300',2),
	 (NULL,'Rua dos navegantes, 61',2),
	 (NULL,'Rua Setubal, 500',2),
	 ('22010-000','Av. Atlântica, 290',5),
	 ('22010-000','Av. Engenheiro Alfredo Correa Daut, 220',1);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 (NULL,'Avenida Brasil, 1230',7),
	 (NULL,'Avenida Presidente Getúlio Vargas, 1431',6),
	 (NULL,'Beco do Boticário, 88',4),
	 ('22010-000','Linha vermelha, 240',6),
	 (NULL,'Rua da Alfândega, 098',4),
	 (NULL,'Rua do Ouvidor, 943',4),
	 (NULL,'Rua Manuel Carneiro, 567',2),
	 ('90410-005','Av. Ipiranga, 5426',2),
	 ('90410-005','Av. Protásio Alves, 1578',3),
	 (NULL,'Avenida assis brasil, 987',1);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 (NULL,'Avenida carlos gomes, 87',3),
	 (NULL,'Avenida farrapos, 906',3),
	 (NULL,'Avenida ipiranga, 432',2),
	 (NULL,'Avenida protássio alves, 12',3),
	 (NULL,'Avenida sete de setembro, 234',1),
	 (NULL,'Avenida beira mar norte, 100',3),
	 (NULL,'avenida beira mar sul, 100',6),
	 (NULL,'Avenida Sete de Setembro, 2334',1),
	 (NULL,'Rua das Piraúnas, 234',3),
	 (NULL,'Avenida 9 de Julho, 100',4);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 (NULL,'Avenida Cruzeiro do Sul, 14',5),
	 (NULL,'Avenida Paulista, 232',1),
	 (NULL,'Avenida Presidente Getúlio Vargas, 237',7),
	 (NULL,'Avenida sete de setembro, 2334',1),
	 ('01413-100','R. Augusta, 2077',7),
	 (NULL,'Rua Oscar Freire, 765',7),
	 ('01413-100','Rua São João, 477',3),
	 (NULL,'Rua Emiliano Perneta, 34',39),
	 (NULL,'Avenida Paulista, 232',46),
	 (NULL,'Avenida Paulista, 232',48);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 (NULL,'Avenida Cruzeiro do Sul, 14',51),
	 (NULL,'Avenida sete de setembro, 234',52),
	 (NULL,'Avenida Cruzeiro do Sul, 14',53),
	 ('22010-000','Av. Atlântica, 290',54),
	 (NULL,'Avenida Paulista, 232',55),
	 ('22010-000','Av. Engenheiro Alfredo Correa Daut, 220',56),
	 (NULL,'Avenida Cruzeiro do Sul, 14',57),
	 (NULL,'Avenida Paulista, 232',58),
	 (NULL,'Avenida Cruzeiro do Sul, 14',59),
	 ('80420-000','R. Comendador Araújo, 152',60);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 (NULL,'Avenida assis brasil, 987',61),
	 ('22010-000','Av. Engenheiro Alfredo Correa Daut, 220',62),
	 ('22010-000','Av. Atlântica, 290',63),
	 (NULL,'Avenida sete de setembro, 2334',64),
	 (NULL,'Avenida Presidente Getúlio Vargas, 985',65),
	 (NULL,'Avenida Sete de Setembro, 2334',66),
	 (NULL,'Avenida assis brasil, 987',67),
	 (NULL,'Avenida Presidente Getúlio Vargas, 985',68),
	 (NULL,'Avenida Sete de Setembro, 2334',69),
	 (NULL,'Avenida Presidente Getúlio Vargas, 985',70);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 ('22010-000','Av. Atlântica, 290',71),
	 ('22010-000','Av. Engenheiro Alfredo Correa Daut, 220',72),
	 (NULL,'Avenida Paulista, 232',73),
	 ('22010-000','Av. Atlântica, 290',74),
	 (NULL,'Avenida sete de setembro, 2334',75),
	 (NULL,'Avenida Sete de Setembro, 2334',76),
	 (NULL,'Rua Emiliano Perneta, 34',77),
	 ('22010-000','Av. Atlântica, 290',78),
	 (NULL,'Avenida assis brasil, 987',79),
	 (NULL,'Avenida Paulista, 232',80);
INSERT INTO Endereco (end_cep,end_descricao,bai_id) VALUES
	 ('22010-000','Av. Atlântica, 290',81);

-- Insere os dados na tabela Estado Civil
insert into EstadoCivil values ('Solteiro');
insert into EstadoCivil values ('Casado');
insert into EstadoCivil values ('Separado');
insert into EstadoCivil values ('Divorciado');
insert into EstadoCivil values ('Viúvo');

-- Insere os dados na tabela Gênero
insert into Genero values (1, 'Feminino');
insert into Genero values (2, 'Masculino');

-- Insere os dados na tabela Cliente
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Ricardo Santos','1980-01-02',2,4,17),
	 (N'Maria de Jesus','1995-02-22',1,4,19),
	 (N'Helena Araújo Botelho','1999-03-31',1,5,4),
	 (N'Alberto Guimarães','1993-08-02',2,3,6),
	 (N'João Ubaldo Milhões','2000-12-28',2,1,9),
	 (N'Ana Beatriz Machado','2001-09-21',1,2,1),
	 (N'Afonso Silva e Costa','2001-10-17',2,4,8),
	 (N'João Souza e Silva','1997-04-26',2,4,2),
	 (N'Euclides da Cunha e Costa','1993-02-03',2,2,15),
	 (N'Paulo Souza Coelho','1981-03-15',2,3,4);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Dan Marcus Cortes','2003-04-13',2,2,14),
	 (N'Agnaldo Silva jardim','1996-05-25',2,3,3),
	 (N'Lauro César Silva','1992-06-12',2,1,13),
	 (N'Adelaide Amaral Muniz','1980-07-11',1,1,13),
	 (N'Gilberto Braga Santos','1994-10-08',2,1,5),
	 (N'Helana Souza Brito','1982-11-06',1,1,14),
	 (N'Adriano Souza','1996-12-12',2,4,16),
	 (N'Alceu Silva','1997-01-11',2,5,20),
	 (N'Alessandro Guimarães','2000-10-27',2,1,6),
	 (N'Alessandro da Rosa Curvello ','2001-11-26',2,1,1);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Ricardo Santos','1965-01-02',2,5,19),
	 (N'Maria de Jesus','1975-02-22',1,2,6),
	 (N'Helena Araújo Botelho','1970-03-31',1,2,9),
	 (N'Alberto Guimarães','1980-08-02',2,2,13),
	 (N'João Ubaldo Milhões','1979-12-28',2,1,7),
	 (N'Ana Beatriz Machado','1988-09-21',1,5,2),
	 (N'Afonso Silva e Costa','1990-10-17',2,3,5),
	 (N'João Souza e Silva','1987-04-26',2,1,17),
	 (N'Euclides da Cunha e Costa','1973-02-03',2,3,12),
	 (N'Paulo Souza Coelho','1981-03-15',2,1,6);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Dan Marcus Cortes','1983-04-13',2,5,3),
	 (N'Agnaldo Silva jardim','1986-05-25',2,1,3),
	 (N'Lauro César Silva','1977-06-12',2,2,10),
	 (N'Adelaide Amaral Muniz','1990-07-11',1,4,4),
	 (N'Gilberto Braga Santos','1984-10-08',2,2,7),
	 (N'Helana Souza Brito','1982-11-06',1,1,4),
	 (N'Adriano Souza','1996-12-12',2,1,1),
	 (N'Alceu Silva','1997-01-11',2,5,7),
	 (N'Alessandro Guimarães','1990-10-27',2,1,14),
	 (N'Alessandro da Rosa Curvello ','1990-11-26',2,4,6);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Alessandro Lesina Giordano ','1973-02-13',2,5,9),
	 (N'Alvaro Souza','1973-03-15',2,5,8),
	 (N'Alvaro Costa Duarte ','1983-04-23',2,3,12),
	 (N'Ana marcela estaves M.B. Fagundes ','1983-05-23',1,1,9),
	 (N'Ana P. Munhoz ','1977-06-22',1,4,1),
	 (N'Ana paula da costa rodrigues ','1977-07-22',1,5,7),
	 (N'Ana Paula da S. Gonçalves ','1984-10-18',1,2,16),
	 (N'Ana paula Munhoz ','1984-11-17',1,1,17),
	 (N'Ana paula Schardosin ','1996-12-22',1,5,8),
	 (N'Anderson Silva','1997-01-21',2,1,15);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Anderson Barros ','1990-11-06',2,4,9),
	 (N'Anderson Mello Tatsch ','1990-12-06',2,5,19),
	 (N'Angeline Guimarães','1991-01-05',2,1,19),
	 (N'Angelo Guimarães','1973-03-25',2,3,5),
	 (N'Angelo Antonello Borges ','1973-04-24',2,1,13),
	 (N'Antonio Marques Dias Alves ','1983-06-02',2,3,11),
	 (N'Arlete Souza','1983-07-02',1,2,11),
	 (N'Arturo Ferraz Castillo ','1977-08-01',2,4,13),
	 (N'Augusto Mazzui Pacheco ','1977-08-31',2,1,5),
	 (N'Bettina Garcia da Rosa Ganicoche ','1984-11-27',1,4,19);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Bianca Aranda de Souza ','1984-12-27',1,5,15),
	 (N'Bianca Neves Peralta ','1997-01-31',1,3,1),
	 (N'Carla Cristina Soares Flores ','1990-11-16',1,4,8),
	 (N'Carlos Alberto Soares Ferreira ','1990-12-16',2,3,18),
	 (N'Carlos Eduardo ','1991-01-15',2,3,7),
	 (N'Carlos Gros Leite ','1991-02-14',2,5,18),
	 (N'Carlos Lucio C de Barros Lampert ','1973-05-04',2,3,13),
	 (N'Carlos Maurilio Guedes Martins ','1973-06-03',2,4,11),
	 (N'Caroline Rodrigues Dias ','1983-07-12',1,5,11),
	 (N'Claudio Vilela','1983-08-11',2,2,15);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Cleberson Silva de Azevedo ','1977-09-10',2,1,6),
	 (N'Cristiane Guimarães','1977-10-10',1,4,8),
	 (N'Cristiano Souza','1985-01-06',2,1,11),
	 (N'Cristiano Gonçalves Catalãn ','1997-02-10',2,5,17),
	 (N'Danielle Maria Cadore Cuty ','1997-03-12',1,1,1),
	 (N'Denis Edson Rodrigues Neves ','1990-12-26',2,4,19),
	 (N'Djalma da Luz Bello ','1991-01-25',2,4,20),
	 (N'Djama Vilela','1991-02-24',2,2,10),
	 (N'Edmilson Alexandre P. Laranjeira ','1991-03-26',2,2,11),
	 (N'Eduardo ','1973-06-13',2,1,17);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Eduardo Rodrigues Kotz ','1973-07-13',2,2,18),
	 (N'Elias Quevedo Madríl ','1983-08-21',2,5,7),
	 (N'Elisiane Guimarães','1983-09-20',1,2,3),
	 (N'Elizabeth Souza de Souza ','1977-10-20',1,1,11),
	 (N'Fabiano Rodrigues Machado ','1985-01-16',2,4,20),
	 (N'Fabio Souza','1985-02-15',2,5,16),
	 (N'Fábio Luiz Nunes Dias ','1997-03-22',2,4,11),
	 (N'Fernanda Moraes da Silveira ','1997-04-21',1,4,20),
	 (N'Fernando Musy Gomes de Freitas ','1991-02-04',2,4,20),
	 (N'Flavia Guimarães','1991-03-06',1,1,15);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Flavio Roberto Ribeiro Fernandes ','1991-04-05',2,4,15),
	 (N'Francis Souza','1991-05-05',1,5,2),
	 (N'Francis Machado Gonçalves ','1973-07-23',1,3,6),
	 (N'Francisco Silva','1973-08-22',2,3,19),
	 (N'Franco Souza','1983-09-30',2,3,15),
	 (N'Franco Sampaio ','1977-10-30',2,1,19),
	 (N'Geraldo Pinto','1977-11-29',2,5,13),
	 (N'Giancarlo Amarantes','1985-02-25',2,5,5),
	 (N'Gleiser Servilho','1985-03-27',2,2,20),
	 (N'Gustavo Pedrotti ','1997-05-01',2,4,16);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Héber Benites ','1997-05-31',2,5,18),
	 (N'Helena Sampaio','1991-03-16',1,1,7),
	 (N'Isidoro Becker Guggiana ','1991-04-15',2,1,17),
	 (N'Ivandete Gomes da Silva ','1991-05-15',1,5,7),
	 (N'Izabel C da Cunha Dos Santos ','1991-06-14',1,3,20),
	 (N'Jose Antonio ','1973-09-01',2,3,2),
	 (N'José Antonio de Oliveira Neto ','1983-10-10',2,3,5),
	 (N'Juliana Santos','1983-11-09',1,3,18),
	 (N'Julio Carlos S. A. Maciel ','1977-12-09',2,1,17),
	 (N'Julyano Neto','1978-01-08',2,5,20);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Kleber Santos','1985-04-06',2,2,16),
	 (N'Lennard M Laprebendere Delgado ','1985-05-06',2,5,2),
	 (N'Leonardo Augusto B Abbondanza ','1997-06-10',2,2,20),
	 (N'Leonardo Barbosa Alves ','1997-07-10',2,3,18),
	 (N'Leonardo de Mattos Asconavieta ','1991-04-25',2,3,16),
	 (N'Leonardo Ribeiro Couto ','1991-05-25',2,2,20),
	 (N'Liana Delgado','1991-06-24',1,3,20),
	 (N'Luciana Pimenta de M. Luderitz ','1973-09-11',1,1,16),
	 (N'Luciano Lopes Callero ','1973-10-11',2,4,5),
	 (N'Luciano Thalheimer Moraes ','1983-11-19',2,1,3);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Lucieli Giudice da Silva ','1983-12-19',2,4,2),
	 (N'Luis Alberto ','1978-01-18',2,5,17),
	 (N'Luiz Carlos ','1978-02-17',2,1,20),
	 (N'Luiz Fernando Apottia Garrafiel ','1985-05-16',2,5,9),
	 (N'Luiz Henrique Pouey Gedres ','1985-06-15',2,5,13),
	 (N'Maria Alice ','1997-07-20',1,1,6),
	 (N'Maico Moraes','1997-08-19',2,4,1),
	 (N'Maico Reis Newysks ','1991-06-04',2,2,19),
	 (N'Marcelo Alves','1991-07-04',2,2,12),
	 (N'Marcelo Antunes Mendes ','1991-08-03',2,2,13);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Marcia Cristiane Peres Maciel ','1973-10-21',1,4,6),
	 (N'Márcio Mendes','1973-11-20',2,2,10),
	 (N'Marcio Andre Costa Zart ','1983-12-29',2,3,11),
	 (N'Marcio Dirnei Flores Soares ','1984-01-28',2,4,19),
	 (N'Marcio Guedes Grassi ','1978-02-27',2,2,8),
	 (N'Marcio Laroca ','1978-03-29',2,1,17),
	 (N'Marcio Melo Alves ','1985-06-25',2,1,20),
	 (N'Marcio reis  ','1985-07-25',2,4,17),
	 (N'Marco Rafael Gonzales Viera ','1997-08-29',2,4,6),
	 (N'Marcos Giovani Barboza Hermanns ','1991-06-14',2,1,10);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Maria Alice de Leóh ','1991-07-14',1,3,12),
	 (N'Maria Cristina ','1991-08-13',1,3,10),
	 (N'Maria Fernanda Aragones Almeida ','1991-09-12',1,3,20),
	 (N'Mariana Gil Pirrongelli ','1973-11-30',1,4,20),
	 (N'Mateus da Costa Rodrigues ','1973-12-30',2,4,11),
	 (N'Matheus Rodrigues','1984-02-07',2,3,18),
	 (N'Maurício Gonçalves Trindade Almeida','1984-03-08',2,4,17),
	 (N'Michel Normey ','1978-04-08',2,2,17),
	 (N'Michele Dos Santos Weis ','1978-05-08',1,1,20),
	 (N'Miguel Angelo Pereira Dinis ','1985-08-04',2,5,2);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Milena Talini Baggio ','2000-02-02',1,1,2),
	 (N'Miriam Souza','2000-05-12',2,5,6),
	 (N'Nabil Azmi Husssin ','1991-07-24',2,5,20),
	 (N'Pablo Penteado','1991-11-01',2,4,6),
	 (N'Paulo Roberto de Castro ','1991-12-01',2,1,8),
	 (N'Paulo Roberto Ribeiro ','1973-12-10',2,3,4),
	 (N'Paulo Rodrigues de Macedo ','1974-01-09',2,5,15),
	 (N'Pedro Macedo','1984-02-17',2,3,11),
	 (N'Rafael Amorim ','1984-03-18',2,3,1),
	 (N'Rafael Severo Poli ','1978-04-18',2,5,2);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Rafael Zamberlan ','2000-02-02',2,4,5),
	 (N'Raimundo Amorin de Almeida Filho ','2000-05-12',2,2,1),
	 (N'Raquel Lesina de Lorenzi ','2000-02-12',1,2,9),
	 (N'Renato Filho','2000-05-22',2,1,1),
	 (N'Renato A. Amado ','2000-06-21',2,3,17),
	 (N'Ricardo Neto','1991-11-11',2,3,16),
	 (N'Ricardo Machado Borges ','1991-12-11',2,1,8),
	 (N'Ricardo Marques Lacerda ','1973-12-20',2,5,13),
	 (N'Rimigio Alves','1974-01-19',2,5,13),
	 (N'Robert  Alvarenca','1984-02-27',2,3,2);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Roberta Prado Alves ','2000-02-02',1,4,16),
	 (N'Rodolfo Samuel Jaureguiberry ','2000-05-12',2,3,7),
	 (N'Rodrigo da Silva ','2000-02-12',2,1,19),
	 (N'Rodrigo Da Silva Mendes ','2000-05-22',2,3,18),
	 (N'Rodrigo del campo ','2000-06-21',2,1,9),
	 (N'Rodrigo Domingues da Silva ','2000-06-01',2,4,3),
	 (N'Rodrigo Osto ','2000-07-01',2,1,6),
	 (N'Rodrigo Sacchett dal osto ','1991-11-21',2,4,17),
	 (N'Rodrigo Silva ','1991-12-21',2,4,8),
	 (N'Romy Mariana Irrazabal L. Pintos ','1973-12-30',2,1,16);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Ronaldo Da silva','2000-02-02',2,3,3),
	 (N'Roseli Lourdes da Rocha ','2000-05-12',1,4,17),
	 (N'Roseli Rodrigues Coelho ','2000-02-12',1,3,20),
	 (N'Selma Almeida ','2000-05-22',1,5,14),
	 (N'Sergio Adolfo Silveira Ribeiro ','2000-02-22',2,1,8),
	 (N'Sidnei ','2000-03-23',2,5,14),
	 (N'Sílvio Normey ','2000-07-01',2,5,18),
	 (N'Simone Guimarães','2000-07-31',2,1,15),
	 (N'Soraia Azmi Husein ','2000-07-11',1,4,15),
	 (N'Suelen Coelho','2000-08-10',2,5,10);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Talis Gonçalves','1991-12-31',2,4,2),
	 (N'Talis Magalhes Saldanha ','1992-01-30',2,3,16),
	 (N'Tatiana Loreto Alves ','2000-02-12',1,3,8),
	 (N'Thiago Sardinha','2000-05-22',2,4,12),
	 (N'Thiago Gonçalves Fernandes ','2000-02-22',2,1,17),
	 (N'Thiago Zamberlan ','2000-03-23',2,4,6),
	 (N'Tiago Alessandro F. Manassi ','2000-03-03',2,4,3),
	 (N'Tiago silva da Silva ','2000-04-02',2,3,20),
	 (N'Valentim Machado Martins ','2000-07-11',2,2,9),
	 (N'Vinicius Bajute Savi ','2000-08-10',2,4,15);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Wagner Quadros ','2000-07-21',2,5,16),
	 (N'Waldelise Cunha','2000-08-20',1,1,9),
	 (N'Walter Yona ','1992-01-10',2,4,6),
	 (N'Willians Giovani M. Rodrigues ','1992-02-09',2,3,8),
	 (N'Yago Anolles Perreira ','2000-02-22',2,2,14),
	 (N'Joao Azambuja','1994-10-18',2,3,6),
	 (N'Jorge Costa','1996-10-27',2,3,19),
	 (N'Jose Torrescassana','1995-02-14',2,2,6),
	 (N'José Roberto','1989-06-05',2,1,16),
	 (N'José Tavera','1999-09-08',2,5,2);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Julio Lucas','1990-11-28',2,2,4),
	 (N'Luis Augusto Lara','2000-05-30',2,5,14),
	 (N'Leonardo Igreja','2001-11-20',2,2,4),
	 (N'Leonardo Ramon','1995-03-31',2,1,10),
	 (N'Lilian Pereira','1998-07-01',1,1,18),
	 (N'Lisandro Torres','1991-10-07',2,2,10),
	 (N'Luis Claúdio Caldeira','1998-04-23',2,2,7),
	 (N'Luis Fernando Ribeiro','1995-03-31',2,5,17),
	 (N'Maira Bittencourt','1990-08-05',1,1,20),
	 (N'Marciano Martins','1991-03-21',2,3,7);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Marcos Spenst','1997-03-14',2,1,10),
	 (N'Maria Helena Spenst','1998-12-29',1,2,7),
	 (N'Marli Oliveira','1992-09-08',1,2,13),
	 (N'Neres Menna Barreto','1993-12-04',2,1,10),
	 (N'José Oliveira','1990-04-02',2,3,8),
	 (N'Paula Marilia Campaz','1993-09-29',1,3,3),
	 (N'Pedro Conrad','1999-03-21',2,2,12),
	 (N'Eyder Franco Sousa Rios','1995-03-13',2,3,14),
	 (N'Deni Jackson','1993-03-22',2,3,19),
	 (N'Altair Marinho Ramos','1999-09-02',2,2,14);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Rosany Correa','1993-06-06',1,4,20),
	 (N'Abdon Qodor','1997-07-02',2,5,14),
	 (N'Sebastião de vicenci','1997-03-13',2,3,8),
	 (N'Sérgio de vicenci','1991-06-14',2,3,8),
	 (N'Valentim Ribeiro','1997-05-09',2,5,19),
	 (N'Vanete Piazola','1997-09-11',1,1,10),
	 (N'Vani Pacheco','2000-03-07',1,2,16),
	 (N'Antonio Sales','1998-02-06',2,1,12),
	 (N'Antonio Marcelo','1992-12-31',2,2,12),
	 (N'Victor Fernandes','1995-09-15',2,2,12);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Ana celina Matarazo','1996-11-18',1,3,16),
	 (N'Antonio Marcelo','1993-09-27',2,4,4),
	 (N'Banura Auristela','1998-12-27',1,3,18),
	 (N'Carlos Alberto Bettina','1991-04-06',2,1,7),
	 (N'Carlos Emilio Padilha','1995-12-28',2,3,10),
	 (N'Clark Oliveira','1989-12-30',2,4,17),
	 (N'Cloves vanderlei lausmann','1993-02-14',2,3,11),
	 (N'Eduardo Salim','1995-06-11',2,3,1),
	 (N'Edgar Silveira','1996-07-10',2,2,5),
	 (N'Fernando Sergio Lobato Dias','1990-08-27',2,4,9);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Vanderlei Fichel','1993-02-16',2,1,15),
	 (N'Francircley Gafree','1994-12-15',1,4,19),
	 (N'Francisco das chagas Rodrigues','1991-05-17',2,3,20),
	 (N'Gilson bortolin','1994-11-22',2,1,9),
	 (N'Gregório Sodré','1993-01-06',2,1,6),
	 (N'Heron Vaz','1991-08-26',2,3,18),
	 (N'John Smith','1990-02-06',2,4,10),
	 (N'Grace Ritchie','1995-05-04',1,5,8),
	 (N'Random J. Patient','1996-04-20',2,3,18),
	 (N'Dennis Doe','1994-05-09',2,3,9);
INSERT INTO Cliente (cli_nome,cli_nascimento,gen_id,eci_id,end_id) VALUES
	 (N'Carla Espinosa','2000-08-31',1,2,1),
	 (N'Laverne Roberts','1996-09-15',1,5,20),
	 (N'Paul Flowers','1989-02-05',2,4,2);

-- Insere os dados na tabela Entregador
INSERT INTO Entregador (ent_nome,ent_nascimento,ent_CNH,ent_CNH_Validade,gen_id,eci_id,end_id) VALUES
	 (N'Valentim Machado Martins ','2000-07-11',N'B5704X','2022-06-04',2,2,9),
	 (N'Vinicius Bajute Savi ','2000-08-10',N'B6645X','2022-06-04',2,4,15),
	 (N'Wagner Quadros ','2000-07-21',N'B8533X','2022-06-04',2,5,16),
	 (N'Waldelise Cunha','2000-08-20',N'B6231X','2022-06-04',1,1,9),
	 (N'Walter Yona ','1992-01-10',N'B8177X','2022-06-04',2,4,6),
	 (N'Willians Giovani M. Rodrigues ','1992-02-09',N'B9843X','2022-06-04',2,3,8),
	 (N'Yago Anolles Perreira ','2000-02-22',N'B8716X','2022-06-04',2,2,14),
	 (N'Joao Azambuja','1994-10-18',N'B8908X','2022-06-04',2,3,6),
	 (N'Jorge Costa','1996-10-27',N'B7802X','2022-06-04',2,3,19),
	 (N'Jose Torrescassana','1995-02-14',N'B9787X','2022-06-04',2,2,6);
INSERT INTO Entregador (ent_nome,ent_nascimento,ent_CNH,ent_CNH_Validade,gen_id,eci_id,end_id) VALUES
	 (N'José Roberto','1989-06-05',N'B9662X','2022-06-04',2,1,16),
	 (N'José Tavera','1999-09-08',N'B7601X','2022-06-04',2,5,2),
	 (N'Julio Lucas','1990-11-28',N'B6679X','2022-06-04',2,2,4),
	 (N'Luis Augusto Lara','2000-05-30',N'B7172X','2022-06-04',2,5,14),
	 (N'Leonardo Igreja','2001-11-20',N'B9827X','2022-06-04',2,2,4),
	 (N'Leonardo Ramon','1995-03-31',N'B7334X','2022-06-04',2,1,10),
	 (N'Lilian Pereira','1998-07-01',N'B9841X','2022-06-04',1,1,18),
	 (N'Lisandro Torres','1991-10-07',N'B6685X','2022-06-04',2,2,10),
	 (N'Luis Claúdio Caldeira','1998-04-23',N'B8121X','2022-06-04',2,2,7),
	 (N'Luis Fernando Ribeiro','1995-03-31',N'B6442X','2022-06-04',2,5,17);
INSERT INTO Entregador (ent_nome,ent_nascimento,ent_CNH,ent_CNH_Validade,gen_id,eci_id,end_id) VALUES
	 (N'Maira Bittencourt','1990-08-05',N'B7439X','2022-06-04',1,1,20),
	 (N'Marciano Martins','1991-03-21',N'B6276X','2022-06-04',2,3,7),
	 (N'Marcos Spenst','1997-03-14',N'B7344X','2022-06-04',2,1,10),
	 (N'Maria Helena Spenst','1998-12-29',N'B8219X','2022-06-04',1,2,7),
	 (N'Marli Oliveira','1992-09-08',N'B7880X','2022-06-04',1,2,13),
	 (N'Neres Menna Barreto','1993-12-04',N'B7012X','2022-06-04',2,1,10),
	 (N'José Oliveira','1990-04-02',N'B5913X','2022-06-04',2,3,8),
	 (N'Paula Marilia Campaz','1993-09-29',N'B7301X','2022-06-04',1,3,3),
	 (N'Pedro Conrad','1999-03-21',N'B6478X','2022-06-04',2,2,12),
	 (N'Eyder Franco Sousa Rios','1995-03-13',N'B6055X','2022-06-04',2,3,14);
INSERT INTO Entregador (ent_nome,ent_nascimento,ent_CNH,ent_CNH_Validade,gen_id,eci_id,end_id) VALUES
	 (N'Deni Jackson','1993-03-22',N'B6214X','2022-06-04',2,3,19),
	 (N'Altair Marinho Ramos','1999-09-02',N'B9050X','2022-06-04',2,2,14),
	 (N'Rosany Correa','1993-06-06',N'B8436X','2022-06-04',1,4,20),
	 (N'Abdon Qodor','1997-07-02',N'B8603X','2022-06-04',2,5,14),
	 (N'Sebastião de vicenci','1997-03-13',N'B7392X','2022-06-04',2,3,8),
	 (N'Sérgio de vicenci','1991-06-14',N'B9133X','2022-06-04',2,3,8),
	 (N'Valentim Ribeiro','1997-05-09',N'B9380X','2022-06-04',2,5,19),
	 (N'Vanete Piazola','1997-09-11',N'B8957X','2022-06-04',1,1,10),
	 (N'Vani Pacheco','2000-03-07',N'B5794X','2022-06-04',1,2,16),
	 (N'Antonio Sales','1998-02-06',N'B9303X','2022-06-04',2,1,12);
INSERT INTO Entregador (ent_nome,ent_nascimento,ent_CNH,ent_CNH_Validade,gen_id,eci_id,end_id) VALUES
	 (N'Antonio Marcelo','1992-12-31',N'B5969X','2022-06-04',2,2,12),
	 (N'Victor Fernandes','1995-09-15',N'B7648X','2022-06-04',2,2,12),
	 (N'Ana celina Matarazo','1996-11-18',N'B6593X','2022-06-04',1,3,16),
	 (N'Antonio Marcelo','1993-09-27',N'B6709X','2022-06-04',2,4,4),
	 (N'Banura Auristela','1998-12-27',N'B7197X','2022-06-04',1,3,18),
	 (N'Carlos Alberto Bettina','1991-04-06',N'B6110X','2022-06-04',2,1,7),
	 (N'Carlos Emilio Padilha','1995-12-28',N'B5848X','2022-06-04',2,3,10),
	 (N'Clark Oliveira','1989-12-30',N'B8025X','2022-06-04',2,4,17),
	 (N'Cloves vanderlei lausmann','1993-02-14',N'B7488X','2022-06-04',2,3,11),
	 (N'Eduardo Salim','1995-06-11',N'B7291X','2022-06-04',2,3,1);
INSERT INTO Entregador (ent_nome,ent_nascimento,ent_CNH,ent_CNH_Validade,gen_id,eci_id,end_id) VALUES
	 (N'Edgar Silveira','1996-07-10',N'B9201X','2022-06-04',2,2,5),
	 (N'Fernando Sergio Lobato Dias','1990-08-27',N'B9117X','2022-06-04',2,4,9),
	 (N'Vanderlei Fichel','1993-02-16',N'B5683X','2022-06-04',2,1,15),
	 (N'Francircley Gafree','1994-12-15',N'B7982X','2022-06-04',1,4,19),
	 (N'Francisco das chagas Rodrigues','1991-05-17',N'B8006X','2022-06-04',2,3,20),
	 (N'Gilson bortolin','1994-11-22',N'B7753X','2022-06-04',2,1,9),
	 (N'Gregório Sodré','1993-01-06',N'B6452X','2022-06-04',2,1,6),
	 (N'Heron Vaz','1991-08-26',N'B6487X','2022-06-04',2,3,18),
	 (N'John Smith','1990-02-06',N'B8532X','2022-06-04',2,4,10),
	 (N'Grace Ritchie','1995-05-04',N'B7406X','2022-06-04',1,5,8);
INSERT INTO Entregador (ent_nome,ent_nascimento,ent_CNH,ent_CNH_Validade,gen_id,eci_id,end_id) VALUES
	 (N'Random J. Patient','1996-04-20',N'B5679X','2022-06-04',2,3,18),
	 (N'Dennis Doe','1994-05-09',N'B6811X','2022-06-04',2,3,9),
	 (N'Carla Espinosa','2000-08-31',N'B9319X','2022-06-04',1,2,1),
	 (N'Laverne Roberts','1996-09-15',N'B6072X','2022-06-04',1,5,20),
	 (N'Paul Flowers','1989-02-05',N'B7775X','2022-06-04',2,4,2);

-- Insere os dados na tabela Loja
insert into Loja (loj_nome, end_id) VALUES ('Restaurante Madero', 1);
insert into Loja (loj_nome, end_id) VALUES ('Churrascaria Barranco', 2);
insert into Loja (loj_nome, end_id) VALUES ('Churrascaria Fogão do chão', 3);
insert into Loja (loj_nome, end_id) VALUES ('Restaurante Frutos do Mar', 4);
insert into Loja (loj_nome, end_id) VALUES ('Ching ling', 4);
insert into Loja (loj_nome, end_id) VALUES ('Lanches Girassol', 13);
insert into Loja (loj_nome, end_id) VALUES ('Restaurante Kitchen', 16);
insert into Loja (loj_nome, end_id) VALUES ('Santa Maria Lanches', 11);
insert into Loja (loj_nome, end_id) VALUES ('Girassol Lanches', 19);
insert into Loja (loj_nome, end_id) VALUES ('Negrão Lanches', 20);
insert into Loja (loj_nome, end_id) VALUES ('Restaurante Matriz', 9);
insert into Loja (loj_nome, end_id) VALUES ('Pizzaria Bella Itália', 7);
insert into Loja (loj_nome, end_id) VALUES ('Restaurante do Dede', 8);
insert into Loja (loj_nome, end_id) VALUES ('Restaurante Arlindo', 12);
insert into Loja (loj_nome, end_id) VALUES ('Dona Artemiza', 19);
insert into Loja (loj_nome, end_id) VALUES ('Edu a Doceira', 15);

-- Insere cotadao de moeda estrangeira
insert into cotacao values ('01012022;220;''USD'';5.6303;5.6309');
insert into cotacao values ('02012022;220;''USD'';5.6303;5.6309');
insert into cotacao values ('03012022;220;''USD'';5.6303;5.6309');
insert into cotacao values ('04012022;220;''USD'';5.6770;5.6776');
insert into cotacao values ('05012022;220;''USD'';5.6622;5.6628');
insert into cotacao values ('06012022;220;''USD'';5.7036;5.7042');
insert into cotacao values ('07012022;220;''USD'';5.6747;5.6753');
insert into cotacao values ('08012022;220;''USD'';5.6747;5.6753');
insert into cotacao values ('09012022;220;''USD'';5.6747;5.6753');
insert into cotacao values ('10012022;220;''USD'';5.6730;5.6736');
insert into cotacao values ('11012022;220;''USD'';5.6345;5.6351');
insert into cotacao values ('12012022;220;''USD'';5.5605;5.5611');
insert into cotacao values ('13012022;220;''USD'';5.5240;5.5246');
insert into cotacao values ('14012022;220;''USD'';5.5343;5.5349');
insert into cotacao values ('15012022;220;''USD'';5.5343;5.5349');
insert into cotacao values ('16012022;220;''USD'';5.5343;5.5349');
insert into cotacao values ('17012022;220;''USD'';5.5052;5.5058');
insert into cotacao values ('18012022;220;''USD'';5.5207;5.5213');
insert into cotacao values ('19012022;220;''USD'';5.4972;5.4978');
insert into cotacao values ('20012022;220;''USD'';5.4160;5.4166');
insert into cotacao values ('21012022;220;''USD'';5.4395;5.4401');
insert into cotacao values ('22012022;220;''USD'';5.4395;5.4401');
insert into cotacao values ('23012022;220;''USD'';5.4395;5.4401');
insert into cotacao values ('24012022;220;''USD'';5.4904;5.4910');
insert into cotacao values ('25012022;220;''USD'';5.4965;5.4971');
insert into cotacao values ('26012022;220;''USD'';5.4318;5.4324');
insert into cotacao values ('27012022;220;''USD'';5.3806;5.3812');
insert into cotacao values ('28012022;220;''USD'';5.3948;5.3954');
insert into cotacao values ('29012022;220;''USD'';5.3568;5.3574');
insert into cotacao values ('30012022;220;''USD'';5.3568;5.3574');
insert into cotacao values ('31012022;220;''USD'';5.3568;5.3574');
insert into cotacao values ('01022022;220;''USD'';5.2804;5.2810');
insert into cotacao values ('02022022;220;''USD'';5.2950;5.2956');
insert into cotacao values ('03022022;220;''USD'';5.3019;5.3025');
insert into cotacao values ('04022022;220;''USD'';5.3278;5.3284');
insert into cotacao values ('05022022;220;''USD'';5.3278;5.3284');
insert into cotacao values ('06022022;220;''USD'';5.3278;5.3284');
insert into cotacao values ('07022022;220;''USD'';5.2907;5.2913');
insert into cotacao values ('08022022;220;''USD'';5.2693;5.2699');
insert into cotacao values ('09022022;220;''USD'';5.2729;5.2735');
insert into cotacao values ('10022022;220;''USD'';5.2095;5.2101');
insert into cotacao values ('11022022;220;''USD'';5.1981;5.1987');
insert into cotacao values ('12022022;220;''USD'';5.1981;5.1987');
insert into cotacao values ('13022022;220;''USD'';5.1981;5.1987');
insert into cotacao values ('14022022;220;''USD'';5.2100;5.2106');
insert into cotacao values ('15022022;220;''USD'';5.1875;5.1881');
insert into cotacao values ('16022022;220;''USD'';5.1624;5.1630');
insert into cotacao values ('17022022;220;''USD'';5.1559;5.1565');
insert into cotacao values ('18022022;220;''USD'';5.1333;5.1339');
insert into cotacao values ('19022022;220;''USD'';5.1333;5.1339');
insert into cotacao values ('20022022;220;''USD'';5.1333;5.1339');
insert into cotacao values ('21022022;220;''USD'';5.0991;5.0997');
insert into cotacao values ('22022022;220;''USD'';5.0605;5.0611');
insert into cotacao values ('23022022;220;''USD'';5.0137;5.0143');
insert into cotacao values ('24022022;220;''USD'';5.1168;5.1174');
insert into cotacao values ('25022022;220;''USD'';5.1388;5.1394');
insert into cotacao values ('26022022;220;''USD'';5.1388;5.1394');
insert into cotacao values ('27022022;220;''USD'';5.1388;5.1394');
insert into cotacao values ('28022022;220;''USD'';5.1388;5.1394');
insert into cotacao values ('01032022;220;''USD'';5.1341;5.1347');
insert into cotacao values ('02032022;220;''USD'';5.1341;5.1347');
insert into cotacao values ('03032022;220;''USD'';5.0473;5.0479');
insert into cotacao values ('04032022;220;''USD'';5.0752;5.0758');
insert into cotacao values ('05032022;220;''USD'';5.0752;5.0758');
insert into cotacao values ('06032022;220;''USD'';5.0752;5.0758');
insert into cotacao values ('07032022;220;''USD'';5.0573;5.0579');
insert into cotacao values ('08032022;220;''USD'';5.0897;5.0903');
insert into cotacao values ('09032022;220;''USD'';5.0088;5.0094');
insert into cotacao values ('10032022;220;''USD'';5.0507;5.0513');
insert into cotacao values ('11032022;220;''USD'';5.0249;5.0255');
insert into cotacao values ('12032022;220;''USD'';5.0249;5.0255');
insert into cotacao values ('13032022;220;''USD'';5.0249;5.0255');
insert into cotacao values ('14032022;220;''USD'';5.0641;5.0647');
insert into cotacao values ('15032022;220;''USD'';5.1308;5.1314');
insert into cotacao values ('16032022;220;''USD'';5.1281;5.1287');
insert into cotacao values ('17032022;220;''USD'';5.0758;5.0764');
insert into cotacao values ('18032022;220;''USD'';5.0405;5.0411');
insert into cotacao values ('19032022;220;''USD'';5.0405;5.0411');
insert into cotacao values ('20032022;220;''USD'';5.0405;5.0411');
insert into cotacao values ('21032022;220;''USD'';4.9660;4.9666');
insert into cotacao values ('22032022;220;''USD'';4.9202;4.9208');
insert into cotacao values ('23032022;220;''USD'';4.8698;4.8704');
insert into cotacao values ('24032022;220;''USD'';4.8061;4.8067');
insert into cotacao values ('25032022;220;''USD'';4.7776;4.7782');
insert into cotacao values ('26032022;220;''USD'';4.7776;4.7782');
insert into cotacao values ('27032022;220;''USD'';4.7776;4.7782');
insert into cotacao values ('28032022;220;''USD'';4.7899;4.7905');
insert into cotacao values ('29032022;220;''USD'';4.7480;4.7486');
insert into cotacao values ('30032022;220;''USD'';4.7491;4.7497');
insert into cotacao values ('31032022;220;''USD'';4.7372;4.7378');
insert into cotacao values ('03012022;978;''EUR'';6,3566;6,3595');
insert into cotacao values ('04012022;978;''EUR'';6,4207;6,4219');
insert into cotacao values ('05012022;978;''EUR'';6,4181;6,4210');
insert into cotacao values ('06012022;978;''EUR'';6,4416;6,4435');
insert into cotacao values ('07012022;978;''EUR'';6,4385;6,4415');
insert into cotacao values ('10012022;978;''EUR'';6,4196;6,4225');
insert into cotacao values ('11012022;978;''EUR'';6,3884;6,3908');
insert into cotacao values ('12012022;978;''EUR'';6,3495;6,3524');
insert into cotacao values ('13012022;978;''EUR'';6,3305;6,3317');
insert into cotacao values ('14012022;978;''EUR'';6,3274;6,3286');
insert into cotacao values ('17012022;978;''EUR'';6,2770;6,2799');
insert into cotacao values ('18012022;978;''EUR'';6,2610;6,2639');
insert into cotacao values ('19012022;978;''EUR'';6,2355;6,2384');
insert into cotacao values ('20012022;978;''EUR'';6,1450;6,1478');
insert into cotacao values ('21012022;978;''EUR'';6,1717;6,1729');
insert into cotacao values ('24012022;978;''EUR'';6,2080;6,2103');
insert into cotacao values ('25012022;978;''EUR'';6,1957;6,1985');
insert into cotacao values ('26012022;978;''EUR'';6,1271;6,1288');
insert into cotacao values ('27012022;978;''EUR'';5,9983;6,0011');
insert into cotacao values ('28012022;978;''EUR'';6,0217;6,0245');
insert into cotacao values ('31012022;978;''EUR'';6,0060;6,0073');
insert into cotacao values ('01022022;978;''EUR'';5,9378;5,9406');
insert into cotacao values ('02022022;978;''EUR'';5,9812;5,9840');
insert into cotacao values ('03022022;978;''EUR'';6,0521;6,0549');
insert into cotacao values ('04022022;978;''EUR'';6,0955;6,0968');
insert into cotacao values ('07022022;978;''EUR'';6,0541;6,0554');
insert into cotacao values ('08022022;978;''EUR'';6,0160;6,0188');
insert into cotacao values ('09022022;978;''EUR'';6,0259;6,0271');
insert into cotacao values ('10022022;978;''EUR'';5,9732;5,9744');
insert into cotacao values ('11022022;978;''EUR'';5,9258;5,9286');
insert into cotacao values ('14022022;978;''EUR'';5,8899;5,8927');
insert into cotacao values ('15022022;978;''EUR'';5,8904;5,8921');
insert into cotacao values ('16022022;978;''EUR'';5,8660;5,8688');
insert into cotacao values ('17022022;978;''EUR'';5,8612;5,8640');
insert into cotacao values ('18022022;978;''EUR'';5,8217;5,8234');
insert into cotacao values ('21022022;978;''EUR'';5,7793;5,7820');
insert into cotacao values ('22022022;978;''EUR'';5,7351;5,7378');
insert into cotacao values ('23022022;978;''EUR'';5,6770;5,6782');
insert into cotacao values ('24022022;978;''EUR'';5,6853;5,6865');
insert into cotacao values ('25022022;978;''EUR'';5,7776;5,7803');
insert into cotacao values ('02032022;978;''EUR'';5,7060;5,7077');
insert into cotacao values ('03032022;978;''EUR'';5,5828;5,5840');
insert into cotacao values ('04032022;978;''EUR'';5,5406;5,5433');
insert into cotacao values ('07032022;978;''EUR'';5,4998;5,5025');
insert into cotacao values ('08032022;978;''EUR'';5,5345;5,5372');
insert into cotacao values ('09032022;978;''EUR'';5,5312;5,5339');
insert into cotacao values ('10032022;978;''EUR'';5,5649;5,5660');
insert into cotacao values ('11032022;978;''EUR'';5,5088;5,5115');
insert into cotacao values ('14032022;978;''EUR'';5,5589;5,5615');
insert into cotacao values ('15032022;978;''EUR'';5,6290;5,6317');
insert into cotacao values ('16032022;978;''EUR'';5,6358;5,6385');
insert into cotacao values ('17032022;978;''EUR'';5,6382;5,6399');
insert into cotacao values ('18032022;978;''EUR'';5,5677;5,5704');
insert into cotacao values ('21032022;978;''EUR'';5,4840;5,4866');
insert into cotacao values ('22032022;978;''EUR'';5,4221;5,4247');
insert into cotacao values ('23032022;978;''EUR'';5,3563;5,3589');
insert into cotacao values ('24032022;978;''EUR'';5,2886;5,2912');
insert into cotacao values ('25032022;978;''EUR'';5,2468;5,2479');
insert into cotacao values ('28032022;978;''EUR'';5,2574;5,2585');
insert into cotacao values ('29032022;978;''EUR'';5,2731;5,2743');
insert into cotacao values ('30032022;978;''EUR'';5,3000;5,3026');
insert into cotacao values ('31032022;978;''EUR'';5,2550;5,2561');

-- Insere os dados na tabela Categoria dos produtos
insert into CategoriaProduto (cat_descricao) VALUES ('Pizza');
insert into CategoriaProduto (cat_descricao) VALUES ('Lanche');
insert into CategoriaProduto (cat_descricao) VALUES ('Japonesa');
insert into CategoriaProduto (cat_descricao) VALUES ('Churrascaria');
insert into CategoriaProduto (cat_descricao) VALUES ('Prato feito');
insert into CategoriaProduto (cat_descricao) VALUES ('Comida Oriental');
insert into CategoriaProduto (cat_descricao) VALUES ('Frutos do Mar');

-- Insere os dados na tabela Produto
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Hamburguer picanha', 30.00, 2, 1);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Salada Ceasar', 20.00, 2, 1);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Palmito na grelha', 45.00, 2, 1);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Rodizio de carnes', 120.00, 4, 2);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Rodizio de massas', 80.00, 4, 2);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Sushi', 70.00, 3, 5);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Moqueca de peixe', 90.00, 7, 4);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Bolinho de bacalheu', 20.00, 7, 4);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Porção camarão frito', 30.00, 7, 4);
insert into produto (pro_descricao, pro_preco, cat_id, loj_id) values ('Sashimi', 75.00, 3, 4);

-- Insere os dados na tabela Forma de pagamento dos pedidos
insert into FormaPagamento (fpg_descricao) values ('Dinheiro');
insert into FormaPagamento (fpg_descricao) values ('Cartão Débito');
insert into FormaPagamento (fpg_descricao) values ('Cartao crédito');
insert into FormaPagamento (fpg_descricao) values ('Ticket refeição');
insert into FormaPagamento (fpg_descricao) values ('Ticket alimentação');

-- Insere dados na tabela Pedido
-- Cursor para gerar os pedidos de acordo com o cliente e sua cidade
declare CursorCliente cursor for 
	select cli_id, cid_id from cliente c
	inner join endereco e
	on c.end_id = e.end_id
	inner join bairro b
	on b.bai_id = e.bai_id

-- variaveis usadas no cursor
Declare @Loja int;
Declare @Cliente int;
Declare @Cidade int;
Declare @entregador int;
Declare @Minimo int;
Declare @Maximo int;
Declare @MaximoPgto int;
Declare @FormaPgto int;
Declare @numeroDias int;
Declare @dataInicio Date;
Declare @DataPedido date;

-- Inicializa variaveis
set @minimo = 0
set @maximo = 90
set @numeroDias = 0 
set @dataInicio = '2022-01-01'

-- Seta o número máximo de forma de pagamento
	set @MaximoPgto = 1;
	if	exists (select count(*) from FormaPagamento)
	begin
		set @MaximoPgto = (select count(*) from FormaPagamento);
	end
-- Abre o curso e posiciona na primeira linha
open CursorCliente
fetch CursorCliente into @cliente, @cidade

-- Leitura do cursor até a última linha
while @@fetch_status = 0
begin
	-- Busca uma loja na mesma cidade do cliente
	set @loja = 1
	set @entregador = 1
	if exists(select * from Loja l	inner join endereco e
		on l.end_id = e.end_id inner join bairro b
		on b.bai_id = e.bai_id and b.cid_id = @cidade)
	begin
		set @loja = (select top 1 Loj_id from Loja l	inner join endereco e
		on l.end_id = e.end_id inner join bairro b
		on b.bai_id = e.bai_id and b.cid_id = @cidade)
	end
	-- Busca um entregador na mesma cidade do cliente
	if exists(select * from entregador l	inner join endereco e
		on l.end_id = e.end_id inner join bairro b
		on b.bai_id = e.bai_id and b.cid_id = @cidade)
	begin
		set @entregador = (select top 1 ent_id from entregador l	inner join endereco e
		on l.end_id = e.end_id inner join bairro b
		on b.bai_id = e.bai_id and b.cid_id = @cidade)
	end
	-- Gera uma data para o pedido. Será entre 01/01 a 31/03/2022
	set @minimo = 1
	set @maximo = 90
	set @numeroDias = ROUND(((@maximo - @minimo) * RAND() + @minimo), 0);
	set @DataPedido = dateadd (dd, @numeroDias, @dataInicio)

	-- Gera uma forma de pagamento
	set @FormaPgto = ROUND(((@MaximoPgto - @minimo) * RAND() + @minimo), 0);

	-- Insere dados no pedido
	insert into Pedido (ped_data, ped_status, loj_id, cli_id, ent_id, fpg_id) values
	(@DataPedido, 9, @Loja, @Cliente, @entregador, @FormaPgto)

	-- Lê a próxima linha do cursor
	fetch CursorCliente into @cliente, @cidade
end

-- Exclui os pedidos com data superior a 31/03/2022
Delete from pedido where ped_data > '2022-03-31'

-- Fecha e desaloca o cursor da memória
Close CursorCliente
Deallocate CursorCliente

-- Insere dados na tabela pedidoProdutos
-- Cursor para gerar os produtos dos pedidos
declare CursorPedido cursor for 
	select ped_id from pedido order by ped_id

-- variaveis usadas no cursor
Declare @produto int;
Declare @pedido int;
Declare @quantidade int;
Declare @precoProduto decimal(12,2);
Declare @i int;
Declare @NumeroProdutos int; -- Total de produtos na tabela produtos
Declare @NumProdutosCliente int -- Número de produtos que serão incluídos no pedido
Declare @Minimo2 int; -- será usada para gerar o loop de pedidos
Declare @Maximo2 int; -- será usada para gerar o loop de pedidos

-- Inicializa variaveis
set @Minimo2 = 1
set @Maximo2 = 5
set @NumeroProdutos = 0
set @NumProdutosCliente = 0

-- Seta a quantidade de pedidos existtentes
set @NumeroProdutos = (select count(*) from produto);

-- Abre o curso e posiciona na primeira linha
open CursorPedido
fetch CursorPedido into @pedido

-- Leitura do cursor até a última linha
while @@fetch_status = 0
begin
	-- Gera aleatoriamente um número de produtos para o pedido
	set @Maximo2 = 5
	set @NumProdutosCliente = 1
	set @NumProdutosCliente = ROUND(((@maximo2 - @minimo2) * RAND() + @minimo2), 0);

	-- Gerar os produtos para o pedido
	set @i = 1
	while @i <= @NumProdutosCliente
	begin
		set @produto = ROUND(((@NumeroProdutos - @minimo2) * RAND() + @minimo2), 0);
		set @maximo2 = 3
		set @quantidade = ROUND(((@maximo - @minimo) * RAND() + @minimo), 0);
		set @precoProduto = (select pro_preco from produto where pro_id = @produto)
		-- Insere dados no Produtos do pedido
		insert into PedidoProduto (ped_id, pro_id, ped_quantidade, pro_preco) values
			(@pedido, @produto, @quantidade, @precoProduto)
		set @i = @i + 1
	end
	-- Lê a próxima linha do cursor
	fetch CursorPedido into @pedido
end

-- FEcha e desaloca o cursor da memória
Close CursorPedido
Deallocate CursorPedido
---------------------------------------------------------------------------------------------------
--ESTUDO DIRIGIDO 1º BIMESTRE - LISTA DE EXERCÍCIOS SQL SERVER

--1. Selecione o nome, a descrição do gênero, a descrição do estado civil e a data de nascimento de todos os
--entregadores por ordem de data de nascimento do mais jovem ao mais velho.
SELECT entregador.ent_nome,
genero.gen_descricao AS genero,
EstadoCivil.eci_nome AS estado_civil,
entregador.ent_nascimento AS data_nascimento
FROM entregador
INNER JOIN genero
ON (entregador.gen_id = genero.gen_id)
INNER JOIN EstadoCivil
ON (entregador.eci_id = EstadoCivil.eci_id)
ORDER BY entregador.ent_nascimento ASC;

--2. Mostre o total de produtos por categoria.
SELECT CategoriaProduto.cat_descricao,
COUNT(produto.pro_id) AS total_produtos
FROM produto
INNER JOIN CategoriaProduto ON produto.cat_id = CategoriaProduto.cat_id
GROUP BY CategoriaProduto.cat_descricao;

--3. Liste o nome e a data de nascimento dos clientes nascidos entre os anos de 1980 e 1990.
SELECT cli_nome AS nome_cliente,
CONVERT(varchar, cli_nascimento, 103) AS data_nascimento
FROM Cliente
WHERE cli_nascimento BETWEEN '1980-01-01' AND '1990-12-31'
ORDER BY cli_nascimento DESC;

--4. Mostre o nome de todos os clientes nascidos no ano de 1991.
SELECT cli_nome AS nome_cliente,
CONVERT(varchar, cli_nascimento, 103)
AS data_nascimento FROM cliente
WHERE YEAR(cli_nascimento) = 1991
ORDER BY cli_nascimento DESC;

--5. Mostre o nome do entregador mais velho.
SELECT ent_nome AS nome_entregador,
CONVERT(varchar, ent_nascimento, 103)
AS data_nascimento FROM entregador
WHERE ent_nascimento = (SELECT MIN(ent_nascimento)
FROM entregador);
SELECT TOP 1 ent_nome FROM entregador ORDER BY ent_nascimento ASC;

--6. Mostre o nome dos clientes que contenham “Silva” em qualquer parte do nome.
SELECT cli_nome FROM cliente WHERE cli_nome LIKE '%Silva%';

--7. Altere a categoria do produto com a descrição 'Hamburguer picanha' para a categoria 4.
UPDATE produto SET cat_id = '4' WHERE pro_descricao = 'Hamburguer picanha';

--8. Inclua o entregador Tiburcio Pericles Schitws, nascido em 26 de fevereiro 1994, com CNH ‘ABC1234’, validade do
--CNH em 30 de dezembro de 2050, do gênero masculino, estado civil solteiro e endereço 1.
INSERT INTO entregador (ent_nome, ent_nascimento, ent_cnh, ent_cnh_validade, gen_id, eci_id, end_id)
VALUES ('Tiburcio Pericles Schitws', '1994-02-26', 'ABC1234', '2050-12-30', 2, 1, 1);

--9. Adicione a coluna tempo de cliente, nome da coluna será cli_tempoCliente, do tipo inteiro, na tabela Cliente
--deixando como valor default o zero (0).
ALTER TABLE Cliente
ADD cli_tempoCliente INT NOT NULL DEFAULT 0;

--10. Verifique se a coluna cli_tempoCliente, da tabela cliente, os valores ficaram como ‘null’, então altere o conteúdo
--deste campo para zero (0) em todos os registros.
UPDATE Cliente SET cli_tempoCliente = 0 WHERE cli_tempoCliente = NULL;

--11. Vamos atualizar o atributo tempo de cliente de cada Cliente. Para isso devemos saber a fórmula do cálculo, que
--será: O ano atual menos o ano de nascimento do Cliente menos 20 anos. Exemplo: Cliente Tiburcio: Ano atual 2023 –
--1994 (ano de nascimento) = 2023 – 1994 = 29 – 20 = 9 (será o tempo de cliente).
UPDATE Cliente SET cli_tempoCliente = YEAR(GETDATE()) - YEAR(data_nascimento) - 20 ;

--12. Usando subconsulta, mostre os produtos da categoria de ‘Lanche'.
SELECT pro_descricao FROM produto
WHERE cat_id = (SELECT cat_id FROM CategoriaProduto
WHERE cat_descricao = 'Lanche');

--13. Em um mesmo resultado apresente o nome dos clientes e dos entregadores e suas respectivas datas de nascimento.
SELECT cli_nome AS nome, cli_nascimento AS data_de_nascimento, 'CLIENTE' AS TIPO FROM Cliente
UNION ALL
SELECT ent_nome AS nome, ent_nascimento AS data_de_nascimento,'ENTREGADOR' AS TIPO FROM entregador;

--14. Crie uma view que mostre o nome, o estado cívil, a data de nascimento, o nome da cidade e o gênero de todos
--os entregadores do delivery. Mostrando a data de nascimento no formato DD/MM/AAAA.
CREATE VIEW vw_entregadores AS
SELECT
entregador.ent_nome AS nome,
EstadoCivil.eci_nome AS estado_civil,
CONVERT(varchar(10), entregador.ent_nascimento, 103) AS data_nascimento,
cidade.cid_nome AS cidade,
genero.gen_descricao AS genero
FROM entregador
INNER JOIN genero ON entregador.gen_id = genero.gen_id
INNER JOIN EstadoCivil ON entregador.eci_id = EstadoCivil.eci_id
INNER JOIN endereco ON entregador.end_id = endereco.end_id
INNER JOIN bairro ON endereco.bai_id = bairro.bai_id
INNER JOIN cidade ON bairro.cid_id = cidade.cid_id

--15. Utilizando a view, criada no exercício anterior, totalize o número de entregadores por cidade.
SELECT cidade AS nome_cidade, COUNT(*) AS total_entregadores FROM vw_entregadores
GROUP BY cidade;

--16. Crie um cursor que liste a data da venda, o dia da semana e o total vendido neste dia. 
--Ex: 01/01/2050 – quinta- feira - R$ 10.000,00.
DECLARE @DataVenda DATE
DECLARE @DiaSemana VARCHAR(20)
DECLARE @TotalVendas DECIMAL(10,2)
DECLARE VendasPorDia CURSOR FOR
SELECT CONVERT(VARCHAR(10), V.DataVenda, 103) AS 'Data da Venda',
DATENAME(WEEKDAY, V.DataVenda) AS 'Dia da Semana',
SUM(V.TotalVenda) AS 'Total de Vendas'
FROM Vendas V
GROUP BY CONVERT(VARCHAR(10), V.DataVenda, 103), DATENAME(WEEKDAY, V.DataVenda)
OPEN VendasPorDia
FETCH NEXT FROM VendasPorDia INTO @DataVenda, @DiaSemana, @TotalVendas
WHILE @@FETCH_STATUS = 0
BEGIN
PRINT @DataVenda + ' - ' + @DiaSemana + ' - R$ ' + CAST(@TotalVendas AS VARCHAR(20))
FETCH NEXT FROM VendasPorDia INTO @DataVenda, @DiaSemana, @TotalVendas
END
CLOSE VendasPorDia
DEALLOCATE VendasPorDia

--17. Altere o cursor, criado na questão anterior, para inserir os resultados 
--em uma tabela temporária e no final mostre o conteúdo da tabela temporária.
CREATE TABLE #VendasPorDia (
DataVenda DATE,
DiaSemana VARCHAR(20),
TotalVendas DECIMAL(10, 2)
)
DECLARE @DataVenda DATE
DECLARE @DiaSemana VARCHAR(20)
DECLARE @TotalVendas DECIMAL(10,2)
DECLARE VendasPorDia CURSOR FOR
SELECT CONVERT(VARCHAR(10), V.DataVenda, 103) AS 'Data da Venda',
DATENAME(WEEKDAY, V.DataVenda) AS 'Dia da Semana',
SUM(V.TotalVenda) AS 'Total de Vendas'
FROM Vendas V
GROUP BY CONVERT(VARCHAR(10), V.DataVenda, 103), DATENAME(WEEKDAY, V.DataVenda)
OPEN VendasPorDia
FETCH NEXT FROM VendasPorDia INTO @DataVenda, @DiaSemana, @TotalVendas
WHILE @@FETCH_STATUS = 0
BEGIN
INSERT INTO #VendasPorDia (DataVenda, DiaSemana, TotalVendas) VALUES (@DataVenda, @DiaSemana,
@TotalVendas)
FETCH NEXT FROM VendasPorDia INTO @DataVenda, @DiaSemana, @TotalVendas
END
CLOSE VendasPorDia
DEALLOCATE VendasPorDia
SELECT * FROM #VendasPorDia
DROP TABLE #VendasPorDia

----------------------------------------------------------------------------------------------------
