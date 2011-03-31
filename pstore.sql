-- phpMyAdmin SQL Dump
-- version 3.3.7deb5build0.10.10.1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Мар 31 2011 г., 19:17
-- Версия сервера: 5.1.49
-- Версия PHP: 5.3.3-1ubuntu9.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `pstore`
--

-- --------------------------------------------------------

--
-- Структура таблицы `comments`
--

DROP TABLE IF EXISTS `comments`;
CREATE TABLE IF NOT EXISTS `comments` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `product_id` int(11) NOT NULL,
  `message` text NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`,`user_id`,`product_id`),
  KEY `fk_comments_products1` (`product_id`),
  KEY `fk_comments_users1` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Связи таблицы `comments`:
--   `product_id`
--       `products` -> `id`
--   `user_id`
--       `users` -> `id`
--

--
-- Дамп данных таблицы `comments`
--


-- --------------------------------------------------------

--
-- Структура таблицы `couriers`
--

DROP TABLE IF EXISTS `couriers`;
CREATE TABLE IF NOT EXISTS `couriers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `deliveries_count` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Дамп данных таблицы `couriers`
--


-- --------------------------------------------------------

--
-- Структура таблицы `courier_product_type`
--

DROP TABLE IF EXISTS `courier_product_type`;
CREATE TABLE IF NOT EXISTS `courier_product_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `courier_id` int(11) NOT NULL,
  `product_type_id` int(11) NOT NULL,
  PRIMARY KEY (`id`,`courier_id`,`product_type_id`),
  KEY `fk_couriers_has_product_type_product_type1` (`product_type_id`),
  KEY `fk_couriers_has_product_type_couriers1` (`courier_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Связи таблицы `courier_product_type`:
--   `courier_id`
--       `couriers` -> `id`
--   `product_type_id`
--       `product_types` -> `id`
--

--
-- Дамп данных таблицы `courier_product_type`
--


-- --------------------------------------------------------

--
-- Структура таблицы `deliveries`
--

DROP TABLE IF EXISTS `deliveries`;
CREATE TABLE IF NOT EXISTS `deliveries` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `sold_product_id` int(11) NOT NULL,
  `courier_id` int(11) NOT NULL,
  `address` varchar(45) NOT NULL,
  PRIMARY KEY (`id`,`courier_id`,`sold_product_id`),
  KEY `fk_deliveries_sold_products1` (`sold_product_id`),
  KEY `fk_deliveries_couriers1` (`courier_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Связи таблицы `deliveries`:
--   `sold_product_id`
--       `sold_products` -> `id`
--   `courier_id`
--       `couriers` -> `id`
--

--
-- Дамп данных таблицы `deliveries`
--


-- --------------------------------------------------------

--
-- Структура таблицы `price`
--

DROP TABLE IF EXISTS `price`;
CREATE TABLE IF NOT EXISTS `price` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `supplier_id` int(11) NOT NULL,
  `product_id` int(11) NOT NULL,
  `price` float NOT NULL,
  `number` int(11) NOT NULL,
  PRIMARY KEY (`id`,`supplier_id`,`product_id`),
  KEY `fk_price_suppliers` (`supplier_id`),
  KEY `fk_price_products1` (`product_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Связи таблицы `price`:
--   `supplier_id`
--       `suppliers` -> `id`
--   `product_id`
--       `products` -> `id`
--

--
-- Дамп данных таблицы `price`
--


-- --------------------------------------------------------

--
-- Структура таблицы `products`
--

DROP TABLE IF EXISTS `products`;
CREATE TABLE IF NOT EXISTS `products` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `product_type_id` int(11) NOT NULL,
  `title` varchar(45) NOT NULL,
  `description` text NOT NULL,
  `extra_charge` float NOT NULL DEFAULT '0',
  `rating` int(11) NOT NULL,
  PRIMARY KEY (`id`,`product_type_id`),
  UNIQUE KEY `title_UNIQUE` (`title`),
  KEY `fk_products_product_type1` (`product_type_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Связи таблицы `products`:
--   `product_type_id`
--       `product_types` -> `id`
--

--
-- Дамп данных таблицы `products`
--

INSERT INTO `products` (`id`, `product_type_id`, `title`, `description`, `extra_charge`, `rating`) VALUES
(1, 1, 'облицовочный', 'красный и белый', 0.5, 5);

-- --------------------------------------------------------

--
-- Структура таблицы `product_types`
--

DROP TABLE IF EXISTS `product_types`;
CREATE TABLE IF NOT EXISTS `product_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `description` text NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Дамп данных таблицы `product_types`
--

INSERT INTO `product_types` (`id`, `name`, `description`) VALUES
(1, 'керпич', 'для кладки'),
(2, 'цимент', 'для крыши');

-- --------------------------------------------------------

--
-- Структура таблицы `sold_products`
--

DROP TABLE IF EXISTS `sold_products`;
CREATE TABLE IF NOT EXISTS `sold_products` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `product_id` int(11) NOT NULL,
  `number` int(11) NOT NULL,
  `isSold` tinyint(4) NOT NULL,
  `date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`,`user_id`,`product_id`),
  KEY `fk_sold_products_users1` (`user_id`),
  KEY `fk_sold_products_products1` (`product_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Связи таблицы `sold_products`:
--   `user_id`
--       `users` -> `id`
--   `product_id`
--       `products` -> `id`
--

--
-- Дамп данных таблицы `sold_products`
--


-- --------------------------------------------------------

--
-- Структура таблицы `suppliers`
--

DROP TABLE IF EXISTS `suppliers`;
CREATE TABLE IF NOT EXISTS `suppliers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `distance` varchar(45) NOT NULL,
  `contacts` tinytext NOT NULL,
  `regdate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `suppliers_name_contacts_UNIQUE` (`name`,`contacts`(20))
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=12 ;

--
-- Дамп данных таблицы `suppliers`
--

INSERT INTO `suppliers` (`id`, `name`, `distance`, `contacts`, `regdate`) VALUES
(2, 'afsdas', '12', 'asdasd', '2011-03-31 17:53:56'),
(4, 'fghfgh', '8', 'gfhdghd', '2011-03-31 17:24:03'),
(6, 'name', '8', 'gfhdghdg', '2011-03-31 17:53:43'),
(11, 'new_name', '12', 'asdasd', '2011-03-31 17:54:06');

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` varchar(45) NOT NULL,
  `password` varchar(45) NOT NULL,
  `lastname` varchar(45) NOT NULL,
  `name` varchar(45) NOT NULL,
  `address` varchar(45) NOT NULL,
  `phone` varchar(45) NOT NULL,
  `email` varchar(45) NOT NULL,
  `reg_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Дамп данных таблицы `users`
--


--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `comments`
--
ALTER TABLE `comments`
  ADD CONSTRAINT `fk_comments_products1` FOREIGN KEY (`product_id`) REFERENCES `products` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_comments_users1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Ограничения внешнего ключа таблицы `courier_product_type`
--
ALTER TABLE `courier_product_type`
  ADD CONSTRAINT `fk_couriers_has_product_type_couriers1` FOREIGN KEY (`courier_id`) REFERENCES `couriers` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_couriers_has_product_type_product_type1` FOREIGN KEY (`product_type_id`) REFERENCES `product_types` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Ограничения внешнего ключа таблицы `deliveries`
--
ALTER TABLE `deliveries`
  ADD CONSTRAINT `fk_deliveries_sold_products1` FOREIGN KEY (`sold_product_id`) REFERENCES `sold_products` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_deliveries_couriers1` FOREIGN KEY (`courier_id`) REFERENCES `couriers` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Ограничения внешнего ключа таблицы `price`
--
ALTER TABLE `price`
  ADD CONSTRAINT `fk_price_suppliers` FOREIGN KEY (`supplier_id`) REFERENCES `suppliers` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_price_products1` FOREIGN KEY (`product_id`) REFERENCES `products` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Ограничения внешнего ключа таблицы `products`
--
ALTER TABLE `products`
  ADD CONSTRAINT `fk_products_product_type1` FOREIGN KEY (`product_type_id`) REFERENCES `product_types` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Ограничения внешнего ключа таблицы `sold_products`
--
ALTER TABLE `sold_products`
  ADD CONSTRAINT `fk_sold_products_users1` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_sold_products_products1` FOREIGN KEY (`product_id`) REFERENCES `products` (`id`) ON DELETE NO ACTION ON UPDATE NO ACTION;
