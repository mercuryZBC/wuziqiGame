/*
 Navicat Premium Data Transfer

 Source Server         : mysql
 Source Server Type    : MySQL
 Source Server Version : 80032
 Source Host           : localhost:3306
 Source Schema         : im

 Target Server Type    : MySQL
 Target Server Version : 80032
 File Encoding         : 65001

 Date: 13/01/2024 19:06:38
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for filetranfer
-- ----------------------------
DROP TABLE IF EXISTS `filetranfer`;
CREATE TABLE `filetranfer`  (
  `sendUserId` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `recvUserId` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `fileName` char(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `originFileName` char(128) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `sendTime` datetime NULL DEFAULT '2023-09-20 21:44:21',
  PRIMARY KEY (`sendUserId`, `recvUserId`, `fileName`) USING BTREE,
  INDEX `recvUserId`(`recvUserId` ASC) USING BTREE,
  CONSTRAINT `filetranfer_ibfk_1` FOREIGN KEY (`sendUserId`) REFERENCES `userinfo` (`userId`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `filetranfer_ibfk_2` FOREIGN KEY (`recvUserId`) REFERENCES `userinfo` (`userId`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for friend
-- ----------------------------
DROP TABLE IF EXISTS `friend`;
CREATE TABLE `friend`  (
  `userId` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `friendId` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  INDEX `userId`(`userId` ASC) USING BTREE,
  INDEX `friendId`(`friendId` ASC) USING BTREE,
  CONSTRAINT `friend_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `userinfo` (`userId`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `friend_ibfk_2` FOREIGN KEY (`friendId`) REFERENCES `userinfo` (`userId`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for game
-- ----------------------------
DROP TABLE IF EXISTS `game`;
CREATE TABLE `game`  (
  `gameid` int NOT NULL AUTO_INCREMENT,
  `gamename` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `gametype` int NOT NULL,
  PRIMARY KEY (`gameid`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 4 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for groupuser
-- ----------------------------
DROP TABLE IF EXISTS `groupuser`;
CREATE TABLE `groupuser`  (
  `groupId` int NOT NULL,
  `groupUserId` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`groupId`, `groupUserId`) USING BTREE,
  INDEX `groupUserId`(`groupUserId` ASC) USING BTREE,
  CONSTRAINT `groupuser_ibfk_1` FOREIGN KEY (`groupId`) REFERENCES `imgroup` (`groupId`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `groupuser_ibfk_2` FOREIGN KEY (`groupUserId`) REFERENCES `userinfo` (`userId`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for imgroup
-- ----------------------------
DROP TABLE IF EXISTS `imgroup`;
CREATE TABLE `imgroup`  (
  `groupId` int NOT NULL AUTO_INCREMENT,
  `groupName` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `groupOwnerId` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `groupIcon` int NOT NULL DEFAULT 13,
  PRIMARY KEY (`groupId`) USING BTREE,
  INDEX `groupOwnerId`(`groupOwnerId` ASC) USING BTREE,
  CONSTRAINT `imgroup_ibfk_1` FOREIGN KEY (`groupOwnerId`) REFERENCES `userinfo` (`userId`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB AUTO_INCREMENT = 19 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for userinfo
-- ----------------------------
DROP TABLE IF EXISTS `userinfo`;
CREATE TABLE `userinfo`  (
  `userId` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `userName` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `passwd` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `iconId` varchar(5) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '1',
  `feeling` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT '分享生活，留住感动',
  PRIMARY KEY (`userId`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Triggers structure for table imgroup
-- ----------------------------
DROP TRIGGER IF EXISTS `my_groupTrigger`;
delimiter ;;
CREATE TRIGGER `my_groupTrigger` AFTER INSERT ON `imgroup` FOR EACH ROW begin
	insert into groupUser values(new.groupId,new.groupOwnerId);
end
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table userinfo
-- ----------------------------
DROP TRIGGER IF EXISTS `myinsert`;
delimiter ;;
CREATE TRIGGER `myinsert` AFTER INSERT ON `userinfo` FOR EACH ROW begin
	insert into friend values(new.userId,new.userId);
end
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
