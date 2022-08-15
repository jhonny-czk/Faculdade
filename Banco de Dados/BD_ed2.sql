/*--------------------------------------------------------------------------------*/
/*                Fundamentos de Banco de Dados: Estudo Dirigido 02               */
/*                      Lista de exercícios SQL (MariaDB)                         */
/* Database Fundamentals. List of SQL exercises (MariaDB) for college assignment. */
/*--------------------------------------------------------------------------------*/
/*  Considere o BD de empregados mostrado a seguir:

Empregado(codEmp, nome, cidade, rua) 
Emprego(codEmp, codComp, salario) 
Companhia(codComp, nome, cidade) 
Gerente(codEmp, codGerente)

*/
CREATE DATABASE /*NOME DO BANCO*/ ed02_E3;
USE /*DATABASE*/ed02_E3;
CREATE TABLE Empregado(
			codEmp INT,
			nome VARCHAR(50),
			cidade VARCHAR(50),
			rua VARCHAR(50),
			PRIMARY KEY (codEmp)
			);

CREATE TABLE Companhia(
			codComp INT,
			nome VARCHAR(50),
			cidade VARCHAR(50),
			PRIMARY KEY (codComp)
			);
	
CREATE TABLE Emprego(
			codEmp INT, 
			codComp INT, 
			salario DECIMAL(10,2),
			FOREIGN KEY (codEmp) references Empregado(codEmp), 
			FOREIGN KEY (codComp) references Companhia(codComp)
			);			

CREATE TABLE Gerente(
			codEmp INT,
			codGerente INT,
			FOREIGN KEY (codEmp) references Empregado(codEmp)
			);
			
 
 INSERT INTO `companhia` (`codComp`, `nome`, `cidade`) VALUES
			(1, 'Unibanco', 'Curitiba'),
			(2, 'Real', 'Floripa'),
			(3, 'Itau', 'São Paulo'),
			(4, 'Bamerindus', 'Curitiba'),
			(5, 'Nu Bank', 'São Paulo'),
			(6, 'Bradesco', 'Rio de janeiro');
	
INSERT INTO `empregado` (`codEmp`, `nome`, `cidade`, `rua`) VALUES
			(1, 'Joaquim', 'Curitiba', 'R1'),
			(2, 'Rodrigo', 'Curitiba', 'R2'),
			(3, 'Felipe', 'Floripa', 'R3'),
			(4, 'Lucas', 'Curitiba', 'R4'),
			(5, 'Maycon', 'Floripa', 'R5'),
			(6, 'Tatiana', 'Floripa', 'R6'),
			(7, 'Cleberson', 'Barra da Tijuca', 'R7'),
			(8, 'Arion', 'Curitiba', 'R8'),
			(9, 'Guilherme', 'Porto Alegre', 'R9');
	
INSERT INTO `emprego` (`codEmp`, `codComp`, `salario`) VALUES
			(1, 1, 1000.00),
			(2, 1, 2000.00),
			(3, 2, 3000.00),
			(4, 3, 5000.00),
			(5, 1, 11000.00),
			(6, 1, 2000.00),
			(6, 2, 1000.00),
			(7, 4, 8800.00),
			(8, 4, 12000.00);
	
INSERT INTO `gerente` (`codEmp`, `codGerente`) VALUES	
			(1, 1), /*Joaquim - Curitiba*/
			(5, 2), /*Maycon* - Floripa*/
			(9, 3); /*Guilherme - Porto Alegre*/

/*Construa as seguintes consultas em SQL:*/

/*Encontre os nomes de todos os empregados que trabalham para o Unibanco.*/
SELECT nome FROM empregado 
WHERE codEmp IN
	(SELECT codEmp FROM emprego 
 	 WHERE codComp =1);

/*Encontre os nomes e cidades onde moram todos os empregados que trabalham no Unibanco.*/
SELECT nome, cidade FROM empregado 
WHERE codEmp IN 
	(SELECT codEmp FROM emprego 
	  WHERE codComp =1);


/* Encontre os nomes, ruas e cidades de todos os empregados que trabalham no Unibanco que ganham mais de R$10.000.*/
SELECT DISTINCT e.nome, e.cidade, e.rua, em.salario 
FROM empregado AS e, emprego AS em 
WHERE e.codEmp IN 
	(SELECT DISTINCT em.codEmp FROM emprego 
	 WHERE em.codComp = 1 AND em.salario >= 10000); 

/*Encontre todos os empregados do BD que moram e trabalham na mesma cidade.
/* Trabalham na mesma empresa e moram na mesma cidade Curitiba */
SELECT DISTINCT e.nome, e.cidade 
FROM empregado AS e, emprego AS em 
WHERE e.codEmp IN 
	(SELECT DISTINCT em.codEmp FROM emprego 
	 WHERE em.codComp = 1) 
	AND e.cidade = 'Curitiba';

/*Trabalham na mesma empresa e moram na mesma cidade Floripa*/
SELECT DISTINCT e.nome, e.cidade 
FROM empregado AS e, emprego AS em 
WHERE e.codEmp IN 
	(SELECT DISTINCT em.codEmp FROM emprego 
 	 WHERE em.codComp = 1) 
	AND e.cidade = 'Floripa';


/*Resolva os seguintes enunciados usando operações de conjuntos e joins.*/
/*Considere o BD de empregados mostrado a seguir:
A empresa possui 2 filiais, com BD distintas.
	
	PRODUTOS1(nome, qtd, valor) 
	DEFEITUOSOS1(nome, data, qtd) 
	PRODUTOS2(nome, qtd, valor) 
	DEFEITUOSOS2(nome, data, qtd)
*/

CREATE DATABASE ed02_E4;
USE ed02_E4;

CREATE TABLE produtos1(
		nome VARCHAR(50),
		qtd INT,
		valor DECIMAL);

CREATE TABLE defeituosos1(
		nome VARCHAR(50),
		dt DATE,
		qtd INT);

CREATE TABLE produtos2(
		nome VARCHAR(50),
		qtd INT,
		valor DECIMAL);

CREATE TABLE defeituosos2(
		nome VARCHAR(50),
		dt DATE,
		qtd INT);
		

INSERT INTO produtos1 (nome, qtd, valor) VALUES
	('SSD Kingston 480GB', 250, 300),
	('Memória Corsair 8GB, DDR4, 2666MHz', 200, 400),
	('Processador AMD Ryzen 5 3600 3.6GHz', 50, 2000),
	('Placa de Vídeo NVIDIA GeForce GTX 1660 Super', 10, 4000);

INSERT INTO produtos2 (nome, qtd, valor) VALUES
	('Teclado', 100, 80),
	('Mouse', 300, 120),
	('Gabinete', 150, 480),
	('Monitor', 70, 1200);

INSERT INTO defeituosos1 (nome, dt, qtd) VALUES
	('SSD Kingston 480GB',  '2022/01/01', 3),
	('Memória Corsair 8GB, DDR4, 2666MHz', '2022/01/02', 2),
	('Processador AMD Ryzen 5 3600 3.6GHz', '2022/01/03', 1),
	('Placa de Vídeo NVIDIA GeForce GTX 1660 Super', '2022/01/04', 0);


INSERT INTO defeituosos2 (nome, dt, qtd) VALUES
	('Teclado', '2022/01/05', 8),
	('Mouse', '2022/01/06', 18),
	('Gabinete', '2022/01/07', 2),
	('Monitor', '2022/01/08', 6);

/*Liste o nome e a quantidade de todos os produtos com defeito na empresa.*/
SELECT nome, qtd FROM  defeituosos1 WHERE qtd > 0 UNION 
	SELECT nome, qtd FROM defeituosos2 WHERE qtd > 0;

/*Liste o nome e a quantidade dos produtos que não possuem nenhuma unidade com defeito.*/
SELECT produtos1.nome, produtos1.qtd FROM produtos1 JOIN defeituosos1 ON 
	produtos1.nome = defeituosos1.nome AND defeituosos1.qtd < 1 UNION 
		SELECT produtos2.nome, produtos2.qtd FROM produtos2 JOIN defeituosos2 ON 
		produtos2.nome = defeituosos2.nome AND defeituosos2.qtd < 1;

/*Liste o nome dos produtos cujas unidades estão todas com defeito.*/
SELECT * FROM produtos1 JOIN defeituosos1 ON 
	produtos1.nome = defeituosos1.nome 
	AND produtos1.qtd < 1 
	AND defeituosos1.qtd > 1 
		UNION SELECT * FROM produtos2 JOIN defeituosos2 ON 
		produtos2.nome = defeituosos2.nome 
		AND produtos2.qtd < 1 
		AND defeituosos2.qtd > 1;

/*Conte o número de produtos que a empresa trabalha.*/
SELECT COUNT(nome) FROM produtos1 UNION 
	SELECT COUNT(nome) FROM produtos2;

/*Conte o total de unidades de produtos da empresa.*/
SELECT COUNT(qtd) FROM produtos1 UNION 
	SELECT COUNT(qtd) FROM produtos2;

/*Mostre o nome e as datas de todos os produtos com defeito, em ordem de tempo.*/
SELECT nome, dt FROM defeituosos1 UNION 
	SELECT nome, dt FROM defeituosos2;

/*Mostre quantos produtos estragaram por mês/ano.*/
SELECT SUM((qtd)) AS total FROM defeituosos1 UNION SELECT 
	SUM((qtd)) AS total FROM defeituosos2;

/*Liste os produtos em estoque que custam mais que R$3.000.*/
SELECT nome, valor FROM produtos1 WHERE valor > 3000 UNION 
	SELECT nome, valor FROM produtos2 WHERE valor > 3000;

/*Liste os produtos que tem mais unidades com defeito do que em estoque.*/
SELECT * FROM produtos1 
	JOIN defeituosos1 ON produtos1.nome = defeituosos1.nome 
	AND defeituosos1.qtd > produtos1.qtd UNION 
		SELECT * FROM produtos2 JOIN defeituosos2 
			ON produtos2.nome = defeituosos2.nome 
			AND defeituosos2.qtd > produtos2.qtd;


/*Com base no estudo de caso da Locadora de Vídeo do Estudo Dirigido do 1º bimestre (Modelagem de BD).
Implemente todas as tabelas no MariaDB, cadastrando alguns dados.
Crie consultas no SQL. Utilize funções de agregação, agrupamentos e joins.
*/

CREATE DATABASE ed_locadora;
USE ed_locadora;

CREATE TABLE categoria (
	codigo INT,
	nome VARCHAR(50),
	PRIMARY KEY (codigo)
	);

CREATE TABLE cliente (
	codigo INT,
	nome VARCHAR(50),
	telefone VARCHAR(15),
	rua VARCHAR(50),
	num_casa INT,
	PRIMARY KEY (codigo)
	);
	
CREATE TABLE filme (
	nome VARCHAR(50),
	nome_ator VARCHAR(50) ,
	nome_real_ator VARCHAR(50),
	dtnasc_ator DATE,
	codigo INT,
	codCat INT,
	PRIMARY KEY (codigo),
	FOREIGN KEY (codCat) REFERENCES categoria(codigo)
	);
	
CREATE TABLE alugar (
	codigo INT,
	codCliente INT,
	codFilme INT,
	PRIMARY KEY(codigo),
	FOREIGN KEY (codCliente) REFERENCES cliente(codigo),
	FOREIGN KEY (codFilme) REFERENCES filme(codigo)
	);


INSERT INTO categoria (codigo,nome) VALUES 
	(001,'Ação'),
	(002,'Comedia'),
	(003,'Animes'),
	(004,'Terror'),
	(005,'Aventura/Fantasia');

INSERT INTO filme (nome, nome_ator, nome_real_ator, 
			dtnasc_ator, codigo, codCat) VALUES 
			('O mascara', 'Stanley Ipkiss', 'Jim Carrey', '1962-01-17', 1000, 002),
			('Silent Hill', 'Christopher', 'Sean Bean', '1959-04-17', 1001, 004),
			('O senhor dos Aneis', 'Frodo', 'Elijah Wood', '1981-01-28', 1010, 005),
			('Naruto Shippuden', 'Naruto', 'Dublador do Naruto', '1972-04-05', 1011, 003),
			('Kimetsu no Yaiba: Demon Slayer', 'Kamado Tanjiro', 'Natsuki Hanae (Dublador)', '1990-01-1', 1100,003);
			
INSERT INTO cliente (codigo, nome, telefone, rua, num_casa) VALUES 
	(0001, 'Jhonny C.', '(41)98788-2030', 'Rua da minha casa', 100),
	(0002, 'Diego F.', '(41)98789-3031', 'Av. Gen. Mario Tourinho', 115),
	(0003, 'Luca P.','(41)98790-4032','Rua das Nações', 1000),
	(0004, 'Leonardo A. C.','(41)98791-5033','Av. Campo Largo', 2100),
	(0005, 'Jean V. A.', '(41)98792-6034','Rua Eng. do Amaral', 180);

INSERT INTO alugar (codigo, codCliente, codFilme) VALUES 
	(1, 0001, 1100),
	(2, 0004, 1001),
	(3, 0003, 1010);


			/*CONSULTAS SQL*/
/*Liste todos os filmes da Locadora*/
SELECT * FROM filme;

/*Liste todos os filmes que estão alugados*/
SELECT nome FROM filme JOIN alugar ON filme.codigo = alugar.codFilme;

/*Liste os filmes e duas categorias*/
SELECT * FROM filme JOIN categoria ON filme.codCat = categoria.codigo;

/*Liste o cliente que está alugando o filme O senhor dos Aneis*/
SELECT nome FROM cliente JOIN alugar ON 
cliente.codigo = alugar.codCliente AND alugar.codFilme = 1010;

/*Liste os clientes que já alugaram filmes*/
SELECT nome FROM cliente JOIN alugar ON
 cliente.codigo = alugar.codCliente;

/*Conte quantos clientes a locadora possui*/
SELECT COUNT(nome) FROM cliente;

/*Conte o total de filmes da locadora*/
SELECT COUNT(nome) FROM filme;

/*Quantos Filmes estão alugados*/
SELECT COUNT(codigo) FROM alugar;

/*Liste os filmes em que possuem o ator Elijah Wood*/
SELECT nome FROM filme WHERE nome_real_ator = 'Elijah Wood';

/*Liste os filmes em que possuem o ator Elijah Wood 
e ao lado do nome do filme, o nome do próprio ator*/
SELECT nome,nome_real_ator FROM filme WHERE nome_real_ator = 'Elijah Wood';

/*Conte quantos filmes do genero Anime*/
SELECT COUNT(nome) FROM filme WHERE	codCat = '003';

/*Conte quantos filmes são do genero Terror*/
SELECT COUNT(nome) FROM filme WHERE	codCat = '004';

/*Liste o nome dos filmes são do genero Terror*/
SELECT nome FROM filme WHERE codCat = '004';


/*Pegue o estudo de caso do Sistema para locadora de veículos do Estudo Dirigido do 1º bimestre (Modelagem de BD).
Implemente todas as tabelas no MariaDB, cadastrando alguns dados.
Crie consultas no SQL, mandando a consulta e uma descrição dela. 
Utilize funções de agregação, agrupamentos e joins.
*/

CREATE DATABASE locadora_veiculos;
USE locadora_veiculos;

CREATE TABLE clienteCPF (
	codigo INT,
	nome VARCHAR(50),
	dtNasc DATE,
	rua VARCHAR(50),
	n_casa INT,
	PRIMARY KEY(codigo)
	);
	
CREATE TABLE clienteCNPJ (
	codigo INT,
	nome VARCHAR(50),
	dtnasc DATE,
	rua VARCHAR(50),
	n_casa INT,
	ie VARCHAR,
	PRIMARY KEY (codigo)
	
CREATE TABLE locacao (
	codigo INT,
	codClienteCPF INT,
	codClienteCNPJ INT,
	PRIMARY KEY (codigo),
	FOREIGN KEY (codClienteCPF) REFERENCES clienteCPF (codigo),
	FOREIGN KEY (codClienteCNPJ) REFERENCES clienteCNPJ (codigo)
	);

CREATE TABLE seguradora (
	codigo INT,
	dtvenc DATE,
	nHabilitacao INT,
	PRIMARY KEY (codigo)
	);

CREATE TABLE revisao (
	codigo INT,
	km INT,
	dtLimpeza DATE,
	dtRevisao DATE,
	PRIMARY KEY(codigo)
	);

CREATE TABLE tipoVeiculo (
	codigo INT,
	nTipoVeiculo VARCHAR(50),
	marca VARCHAR(50),
	modelo VARCHAR(50),
	placa VARCHAR(8),
	nPassageiros INT,
	nChassi VARCHAR(20) /*UNIQUE*/,
	nMotor VARCHAR(10),
	cor VARCHAR(50),
	acessorios VARCHAR(50),
	nPortas INT,
	capacidadeCarga INT,
	codRevisao INT,
	PRIMARY KEY (codigo),
	FOREIGN KEY (codRevisao) REFERENCES revisao (codigo)
	);

CREATE TABLE veiculo (
	codigo INT,
	codTipoVeiculo INT,
	codSeguradora INT,
	PRIMARY KEY( codigo),
	FOREIGN KEY (codTipoVeiculo) REFERENCES tipoVeiculo (codigo),
	FOREIGN KEY (codSeguradora) REFERENCES seguradora (codigo)
	);

CREATE TABLE reserva (
	codigo INT,
	dtEntrega DATE,
	dtPrevissao DATE,
	PRIMARY KEY(codigo) 
	);
	
CREATE TABLE alugado (
	codigo INT,
	codReserva INT,
	pontoEntrega VARCHAR(50),
	dtEntrega DATE,
	PRIMARY KEY(codigo),
	FOREIGN KEY (codReserva) REFERENCES reserva (codigo)
	);
	
CREATE TABLE filial (
	codigo INT,
	nome VARCHAR(50),
	codLoc INT,
	codAlug INT,
	codVeic INT,
	PRIMARY KEY (codigo),
	FOREIGN KEY (codLoc) REFERENCES locacao (codigo),
	FOREIGN KEY (codAlug) REFERENCES alugado (codigo),
	FOREIGN KEY (codVeic) REFERENCES veiculo (codigo)
	);

INSERT INTO clienteCPF () VALUES
			(101,'John', '1992-12-16','Rua Nihon', 20),
			(102,'Victor','1996-09-11','Rua Candido Abreu',100),
			(103,'Luc','1996-11-27','Av Santa Felicidade,',150),
			(104,'Leo','1998-04-15','Av Campo Largo',200);
			
INSERT INTO clienteCNPJ (codigo, nome, dtnasc, rua, n_casa, ie) VALUES
		(201,'Flores', '1989-11-20','Av. Barigui', 2000,'90500683-55'),
		(202,'Didi','1980-10-11','Av. Tuiuti',1000,'ISENTO');
		
INSERT INTO locacao (codigo, codClienteCPF, codClienteCNPJ) VALUES
		(301,NULL,201),
		(302,101,NULL);

INSERT INTO seguradora (codigo, dtvenc, nHabilitacao) VALUES
		(401,'2025-01-30', 012345678);
		
INSERT INTO revisao (codigo, km, dtLimpeza, dtRevissao) VALUES
	(501, 5000,'2022-06-30','2022-05-20'),
	(502, 3000,'2022-06-30','2022-05-25');
	
INSERT INTO tipoVeiculo (codigo, nTipoVeiculo/*VARCHAR*/, marca, modelo, placa /*VARCHAR*/,
					nPassageiros, nChassi/*VARCHAR*/, nMotor/*VARCHAR*/, cor, acessorios/*VARCHAR(50)*/, 
					nPortas, capacidadeCarga/*Kg*/, codRevisao) VALUES	
	(601,'SUV','Honda','HR-V','AAA-1A00',5,'01234567890123456','0123456789','Vermelho Mercúrio Perolizado',
	'Farol de neblina',4,1276,501),
	(602,'Sport', 'Honda','Civic','CCC-2A00', 5,'12345678901234567','52WV012345', 'Pérola Negra Cristal',
	'Soleira iluminada',4,600,502);
	
INSERT INTO veiculo (codigo, codTipoVeiculo, codSeguradora) VALUES
	(701,601,401),
	(702,602,401);
	
INSERT INTO reserva(codigo,	dtEntrega, dtPrevissao) VALUES
	(801, '2022-07-15','2022-07-30');
	
INSERT INTO alugado (codigo,codReserva,pontoEntrega,dtEntrega) VALUES
	(901,801,'Matriz', '2022-07-16');
	
INSERT INTO filial (codigo, nome,codLoc,codAlug,codVeic) VALUES
	(1001,'Filial_01',301,901,701);


				/* consultas no SQL,*/
/*Liste todos os clientes pessoa física*/
SELECT * FROM clienteCPF;

/*Conte todos os clientes pessoa física*/
SELECT COUNT(nome) FROM clientecpf;

/*Liste as datas de nascimento de todos os clientes (P. Fisica e Juridica)*/
SELECT dtNasc FROM clientecpf
UNION
SELECT dtnasc FROM clientecnpj

/*Liste todos os carros da locadora*/
SELECT * FROM veiculo;

/* Liste todas as categorias de veiculo*/
SELECT ntipoveiculo FROM tipoveiculo;

/*Liste todas as marcas de carro*/
SELECT marca FROM tipoveiculo GROUP BY marca;

/*Conte quantos carros a locadora possui*/
SELECT COUNT(codigo) FROM veiculo;

/*Liste  as informações sobre a caracteristica dos veiculos da locadora*/
SELECT * FROM  tipoveiculo;

/*Liste o nome de todos os veiculos da locadora*/
SELECT modelo FROM veiculo, tipoveiculo GROUP BY modelo;

/*Liste os veiculos que tem a cor vermelha*/
SELECT * FROM tipoveiculo WHERE cor LIKE '%vermelho%';

/*Liste os veiculos que possuem Farol de neblina*/
SELECT codigo, modelo, marca, placa, Ntipoveiculo FROM tipoveiculo WHERE acessorios LIKE '%farol de neblina%';

/*Liste todos os veiculos que possuem acessorios*/
/*SELECT * FROM tipoveiculo WHERE acessorios IS NOT NULL;*/
SELECT codigo, modelo, marca, placa FROM tipoveiculo WHERE acessorios IS NOT NULL;

/*Liste o nome do modelo do carro e a data da sua revisao*/
SELECT modelo, dtRevisao FROM tipoveiculo, revisao GROUP BY modelo;

/*Liste a data da ultima revisao dos veiculos SUV*/
SELECT dtRevisao FROM revisao 
JOIN tipoveiculo ON revisao.codigo = tipoveiculo.codRevisao 
AND tipoveiculo.nTipoVeiculo = 'SUV';
