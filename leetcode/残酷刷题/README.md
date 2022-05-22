# 残酷刷题群

- [残酷刷题群](#残酷刷题群)
    - [Problems](#problems)
        - [前缀和](#前缀和)
        - [排序](#排序)
            - [Quick Select](#quick-select)
        - [双指针](#双指针)
        - [堆](#堆)
        - [单调栈](#单调栈)
        - [DP](#dp)
            - [二分图](#二分图)
            - [状态压缩](#状态压缩)
            - [LIS](#lis)
            - [背包](#背包)
            - [subsequence 计数](#subsequence-计数)
            - [二分查找](#二分查找)
        - [并查集](#并查集)
            - [时光倒流](#时光倒流)
        - [回文串 (DP / Manacher)](#回文串-dp--manacher)
        - [最短路](#最短路)
        - [数学](#数学)
            - [质数筛](#质数筛)
            - [公约数](#公约数)
        - [搜索](#搜索)
            - [BFS](#bfs)
            - [拓扑排序](#拓扑排序)
            - [DFS](#dfs)
            - [位运算枚举](#位运算枚举)
        - [表达式求值](#表达式求值)
        - [状态机](#状态机)
        - [链表](#链表)
        - [欧拉路径](#欧拉路径)
        - [LCA (最近公共祖先)](#lca-最近公共祖先)
        - [基环树](#基环树)
        - [字符串哈希](#字符串哈希)
        - [括号匹配](#括号匹配)
        - [分治 (Divide and Conquer)](#分治-divide-and-conquer)
        - [扫描线 (Sweep Line)](#扫描线-sweep-line)
    - [Links](#links)

## Problems

### 前缀和

- 2025. Maximum Number of Ways to Partition an Array
- 1685. Sum of Absolute Differences in a Sorted Array
- 2121. Intervals Between Identical Elements
- 850. Rectangle Area II, 二维差分
- 2132. Stamping the Grid
- 1109. Corporate Flight Bookings: 差分
- 2251. Number of Flowers in Full Bloom: 差分

### 排序

- 1996. The Number of Weak Characters in the Game
- 2007. Find Original Array From Doubled Array

#### Quick Select

- 973. K Closest Points to Origin
- 347. Top K Frequent Elements

### 双指针

- 2009. Minimum Number of Operations to Make Array Continuousg
- 1004. Max Consecutive Ones III
- 2024. Maximize the Confusion of an Exam
- 424. Longest Repeating Character Replacement
- 930. Binary Subarrays With Sum
- 2106. Maximum Fruits Harvested After at Most K Steps

### 堆

- 2102. Sequentially Ordinal Rank Tracker
- 2163. Minimum Difference in Sums After Removal of Elements
- 1368. Minimum Cost to Make at Least One Valid Path in a Grid: 搜索
- 1514. Path with Maximum Probability
- 882. Reachable Nodes In Subdivided Graph: dijkstra
- 787. Cheapest Flights Within K Stops: 二维的 dijkstra，有点类似 dp 的思想

### 单调栈

- 316. Remove Duplicate Letters
- 402. Remove K Digits
- 42. Trapping Rain Water

### DP

- 1959. Minimum Total Space Wasted With K Resizing Operations
- 1105. Filling Bookcase Shelves
- 1043. Partition Array for Maximum Sum
- 1977. Number of Ways to Separate Numbers
    - LCS + 区间 DP
- 2008. Maximum Earnings From Taxi
- 1235. Maximum Profit in Job Scheduling
- 1751. Maximum Number of Events That Can Be Attended II
- 1478. Allocate Mailboxes
    - DP + 货仓选址
- 1277. Count Square Submatrices with All Ones
- 2088. Count Fertile Pyramids in a Land
- 1473. Paint House III
    - 线性 DP
- 1638. Count Substrings That Differ by One Character
- 2167. Minimum Time to Remove All Cars Containing Illegal Goods
- 2209. Minimum White Tiles After Covering With Carpets

#### 二分图

- 1595. Minimum Cost to Connect Two Groups of Points

#### 状态压缩

- 1986. Minimum Number of Work Sessions to Finish the Tasks
    - 子集遍历
- 1494. Parallel Courses II
- 1655. Distribute Repeating Integers
- 2002. Maximum Product of the Length of Two Palindromic Subsequences
- 1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix
- 1452. People Whose List of Favorite Companies Is Not a Subset of Another List

#### LIS

- 300. Longest Increasing Subsequence
- 1964. Find the Longest Valid Obstacle Course at Each Position
- 1713. Minimum Operations to Make a Subsequence
- 354. Russian Doll Envelopes
    - w 递增，h 递减排序，在 h 上求 LIS 一定就是答案

#### 背包

- 1981. Minimize the Difference Between Target and Chosen Elements

#### subsequence 计数

- 940. Distinct Subsequences II
- 1987. Number of Unique Good Subsequences
- 1994. The Number of Good Subsets

#### 二分查找

- 2054. Two Best Non-Overlapping Events
- 1235. Maximum Profit in Job Scheduling
- 1751. Maximum Number of Events That Can Be Attended II
- 1300. Sum of Mutated Array Closest to Target
- 1802. Maximum Value at a Given Index in a Bounded Array
- 1201. Ugly Number III.js
- 二分 + 容斥原理 + lcm
- 1648. Sell Diminishing-Valued Colored Balls

### 并查集

- 1627. Graph Connectivity With Threshold
- 2092. Find All People With Secret
    - 并查集，宽搜都可以做
- 5995. Groups of Strings

#### 时光倒流

- 1970. Last Day Where You Can Still Cross
- 803. Bricks Falling When Hit

### 回文串 (DP / Manacher)

- 5. Longest Palindromic Substring
- 1960. Maximum Product of the Length of Two Palindromic Substrings
    - Manacher + 双指针
- 214. Shortest Palindrome

### 最短路

- 1976. Number of Ways to Arrive at Destination
    - 最短路 + DP

### 数学

#### 质数筛

- 952. Largest Component Size by Common Factor
    - 质数筛 + DP
- 1998. GCD Sort of an Array

#### 公约数

- 2183. Count Array Pairs Divisible by K

### 搜索

- 2014. Longest Subsequence Repeated k Times
- 1755. Closest Subsequence Sum
    - 双向搜索

#### BFS

- 2045. Second Minimum Time to Reach Destination
- 1263. Minimum Moves to Move a Box to Their Target Location
    - Deque, 只有 0 和 1 两个边权

#### 拓扑排序

- 207. Course Schedule
- 210. Course Schedule II
- 2115. Find All Possible Recipes from Given Supplies
- 310. Minimum Height Trees
    - 无向图的拓扑排序

#### DFS

- 543. Diameter of Binary Tree
- 687. Longest Univalue Path
- 124. Binary Tree Maximum Path Sum
- 2056. Number of Valid Move Combinations On Chessboard
    - 非常恶心的一道暴力题，怎么做都能做出来，但是就是题意复杂

#### 位运算枚举

- 1774. Closest Dessert Cost

### 表达式求值

- 227. Basic Calculator II
- 241. Different Ways to Add Parentheses
- 679. 24 Game

### 状态机

- 2055. Plates Between Candles

### 链表

- 206. Reverse Linked List
- 92. Reverse Linked List II
- 25. Reverse Nodes in k-Group
- 2074. Reverse Nodes in Even Length Groups
- 143. Reorder List

### 欧拉路径

- 332. Reconstruct Itinerary
- 2097. Valid Arrangement of Pairs

### LCA (最近公共祖先)

- 236. Lowest Common Ancestor of a Binary Tree
- 1123. Lowest Common Ancestor of Deepest Leaves
- 2096. Step-By-Step Directions From a Binary Tree Node to Another

### 基环树

- 2127. Maximum Employees to Be Invited to a Meeting

### 字符串哈希

- 1044. Longest Duplicate Substring
    - 数据比较强，需要开较大的 Q 取模，只能用 BigInt
- 214. Shortest Palindrome
- 5994. Find Substring With Given Hash Value
- 1923. Longest Common Subpath
- 2223. Sum of Scores of Built Strings
    - 双哈希，可以把 mod 调小一点，不用 BigInt，JS 的 BigInt 效率还是很慢，很容易超时

### 括号匹配

- 2116. Check if a Parentheses String Can Be Valid
- 32. Longest Valid Parentheses

### 分治 (Divide and Conquer)

- 315. Count of Smaller Numbers After Self
- 2179. Count Good Triplets in an Array

### 扫描线 (Sweep Line)

- 56. Merge Intervals

## Links

- https://wisdompeak.github.io/lc-score-board/
- https://docs.google.com/spreadsheets/d/1kBGyRsSdbGDu7DzjQcC-UkZjZERdrP8-_QyVGXHSrB8/edit
