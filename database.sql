
--
-- Database: `furniture`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `admin_id` int(11) NOT NULL,
  `admin_name` varchar(60) NOT NULL,
  `admin_phoneNum` varchar(10) NOT NULL,
  `admin_address` varchar(100) NOT NULL,
  `admin_username` varchar(30) NOT NULL,
  `admin_password` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`admin_id`, `admin_name`, `admin_phoneNum`, `admin_address`, `admin_username`, `admin_password`) VALUES
(1, 'admin', '0123456789', 'a', 'admin', 'admin');

-- --------------------------------------------------------

--
-- Table structure for table `archive`
--

CREATE TABLE `archive` (
  `archive_id` int(11) NOT NULL,
  `furniture_name` varchar(50) NOT NULL,
  `furniture_price` decimal(10,2) UNSIGNED NOT NULL,
  `adminID_add` int(11) NOT NULL,
  `adminID_delete` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `customer_id` int(11) NOT NULL,
  `customer_name` varchar(60) NOT NULL,
  `customer_phoneNum` varchar(10) NOT NULL,
  `customer_address` varchar(100) NOT NULL,
  `customer_username` varchar(30) NOT NULL,
  `customer_password` varchar(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`customer_id`, `customer_name`, `customer_phoneNum`, `customer_address`, `customer_username`, `customer_password`) VALUES
(1, 'customer1', '0123456789', 'a', 'customer1', 'customer1');

-- --------------------------------------------------------

--
-- Table structure for table `furniture_item`
--

CREATE TABLE `furniture_item` (
  `furniture_id` int(11) NOT NULL,
  `furniture_name` varchar(50) NOT NULL,
  `furniture_price` decimal(10,2) UNSIGNED NOT NULL,
  `furniture_stock` int(11) NOT NULL,
  `admin_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `furniture_item`
--

INSERT INTO `furniture_item` (`furniture_id`, `furniture_name`, `furniture_price`, `furniture_stock`, `admin_id`) VALUES
(1, 'chair', 50.00, 2, 1),
(2, 'table', 120.00, 9, 1);

-- --------------------------------------------------------

--
-- Table structure for table `orders`
--

CREATE TABLE `orders` (
  `order_id` int(11) NOT NULL,
  `order_date` date NOT NULL,
  `customer_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `orders`
--

INSERT INTO `orders` (`order_id`, `order_date`, `customer_id`) VALUES
(1, '2024-05-16', 1);

-- --------------------------------------------------------

--
-- Table structure for table `order_furniture`
--

CREATE TABLE `order_furniture` (
  `of_id` int(11) NOT NULL,
  `of_quantity` int(11) NOT NULL,
  `of_totalCost` decimal(10,2) UNSIGNED NOT NULL,
  `order_id` int(11) NOT NULL,
  `furniture_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `order_furniture`
--

INSERT INTO `order_furniture` (`of_id`, `of_quantity`, `of_totalCost`, `order_id`, `furniture_id`) VALUES
(1, 1, 120.00, 1, 2);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`admin_id`);

--
-- Indexes for table `archive`
--
ALTER TABLE `archive`
  ADD PRIMARY KEY (`archive_id`),
  ADD KEY `adminID_add` (`adminID_add`),
  ADD KEY `adminID_delete` (`adminID_delete`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`customer_id`);

--
-- Indexes for table `furniture_item`
--
ALTER TABLE `furniture_item`
  ADD PRIMARY KEY (`furniture_id`),
  ADD KEY `admin_id` (`admin_id`);

--
-- Indexes for table `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`order_id`),
  ADD KEY `customer_id` (`customer_id`);

--
-- Indexes for table `order_furniture`
--
ALTER TABLE `order_furniture`
  ADD PRIMARY KEY (`of_id`),
  ADD KEY `order_id` (`order_id`),
  ADD KEY `furniture_id` (`furniture_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `admin_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `archive`
--
ALTER TABLE `archive`
  MODIFY `archive_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `customer_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `furniture_item`
--
ALTER TABLE `furniture_item`
  MODIFY `furniture_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `orders`
--
ALTER TABLE `orders`
  MODIFY `order_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `order_furniture`
--
ALTER TABLE `order_furniture`
  MODIFY `of_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `archive`
--
ALTER TABLE `archive`
  ADD CONSTRAINT `archive_ibfk_1` FOREIGN KEY (`adminID_add`) REFERENCES `admin` (`admin_id`),
  ADD CONSTRAINT `archive_ibfk_2` FOREIGN KEY (`adminID_delete`) REFERENCES `admin` (`admin_id`);

--
-- Constraints for table `furniture_item`
--
ALTER TABLE `furniture_item`
  ADD CONSTRAINT `furniture_item_ibfk_1` FOREIGN KEY (`admin_id`) REFERENCES `admin` (`admin_id`);

--
-- Constraints for table `orders`
--
ALTER TABLE `orders`
  ADD CONSTRAINT `orders_ibfk_1` FOREIGN KEY (`customer_id`) REFERENCES `customer` (`customer_id`);

--
-- Constraints for table `order_furniture`
--
ALTER TABLE `order_furniture`
  ADD CONSTRAINT `order_furniture_ibfk_1` FOREIGN KEY (`order_id`) REFERENCES `orders` (`order_id`),
  ADD CONSTRAINT `order_furniture_ibfk_2` FOREIGN KEY (`furniture_id`) REFERENCES `furniture_item` (`furniture_id`);