-- phpMyAdmin SQL Dump
-- version 2.11.6
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jul 08, 2008 at 09:16 PM
-- Server version: 5.0.51
-- PHP Version: 5.2.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `h4des`
--

-- --------------------------------------------------------

--
-- Table structure for table `chars`
--

CREATE TABLE `chars` (
  `id` bigint(100) NOT NULL auto_increment,
  `user` bigint(100) NOT NULL,
  `charnum` tinyint(1) NOT NULL,
  `nome` varchar(100) NOT NULL,
  `povo` int(3) NOT NULL default '0',
  `raca` int(3) NOT NULL default '0',
  `profissao` int(3) NOT NULL default '0',
  `sexo` tinyint(1) NOT NULL default '1',
  `arma` bigint(100) NOT NULL default '0',
  `esq` bigint(100) NOT NULL default '0',
  `cabeca` bigint(100) NOT NULL default '0',
  `armadura` bigint(100) NOT NULL default '0',
  `luva` bigint(100) NOT NULL default '0',
  `bota` bigint(100) NOT NULL default '0',
  `calca` bigint(100) NOT NULL default '0',
  `cintura` bigint(100) NOT NULL default '0',
  `capa` bigint(100) NOT NULL default '0',
  `lvl` int(5) NOT NULL default '1',
  `exp` bigint(100) NOT NULL default '0',
  `gold` bigint(100) NOT NULL default '1000',
  `hp` bigint(100) NOT NULL default '100',
  `mp` bigint(100) NOT NULL default '100',
  `hp_max` bigint(100) NOT NULL default '100',
  `mp_max` bigint(100) NOT NULL default '100',
  `str` int(5) NOT NULL default '5',
  `intl` int(5) NOT NULL default '5',
  `sau` int(5) NOT NULL default '5',
  `per` int(5) NOT NULL default '5',
  `car` int(5) NOT NULL default '5',
  `dex` int(5) NOT NULL default '5',
  `agi` int(5) NOT NULL default '5',
  `magia` int(5) NOT NULL default '5',
  `sp` bigint(100) NOT NULL default '0',
  `skp` bigint(100) NOT NULL default '0',
  `guild` bigint(100) NOT NULL default '0',
  `map` bigint(100) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `save_map` bigint(100) NOT NULL,
  `save_x` float NOT NULL,
  `save_y` float NOT NULL,
  `online` tinyint(1) NOT NULL default '0',
  KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `guilds`
--

CREATE TABLE `guilds` (
  `id` bigint(100) NOT NULL,
  `nome` varchar(100) NOT NULL,
  `lider` bigint(100) NOT NULL,
  `lvl` int(5) NOT NULL default '1',
  `exp` bigint(100) NOT NULL default '0',
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `items`
--

CREATE TABLE `items` (
  `id` bigint(100) NOT NULL,
  `char` bigint(100) NOT NULL,
  `vida` bigint(100) NOT NULL,
  KEY `id` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` bigint(100) NOT NULL auto_increment,
  `usuario` varchar(100) NOT NULL,
  `senha` varchar(100) NOT NULL,
  `perm` bigint(100) NOT NULL default '10',
  `warn` bigint(100) NOT NULL default '0',
  `ban` tinyint(1) NOT NULL default '0',
  `lang` varchar(5) NOT NULL default 'en_US',
  `ip` varchar(15) NOT NULL default '0.0.0.0',
  `online` tinyint(1) NOT NULL default '0',
  UNIQUE KEY `usuario` (`usuario`),
  KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1;
