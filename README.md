
# RapiKargo

Desktop application created with C and GTK 3 library. This application allows you to manage the delivery of packages and customer data. Was made as a final project for the "Data Structures and Algorithms" class in İstanbul Medeniyet University.

<img src="https://github.com/WilmerCP/RapiKargo/blob/master/img/main.png" width="500">

## Featured Algorithms

- Merge Sort : Ordering delivery data from lower to longest delivery time

- Insertion Sort : Sorting delivered packages by ID

- Binary Seach : Finding data of an specific delivery by ID

## Featured Data Structures

- Linked List : Holding customer information

- Tree : Mapping delivery routes and calculating distance between cities

- Stack : Keeping track of cargo history for customers

- Binary Heap (Priority Queue) : Processing deliveries in order, from shorter to longer delivery time

<img src="https://github.com/WilmerCP/RapiKargo/blob/master/img/tree.png" width="500">

## Getting Started


### Prerequisites

- GCC C compiler

- GTK3

### Set up

#### 1. Clone the project

```bash
  git clone https://github.com/WilmerCP/RapiKargo.git
```
#### 2. Install gcc

#### On linux (if not installed already)

```bash
  sudo apt-get install gcc
```

#### 3. Install GTK3

#### On linux

```bash
  sudo apt install libgtk-3-dev
```

#### 4. Install pkg-config (recommended for simplicity)

#### On linux

```bash
  sudo apt install pkg-config
```
#### 5. Compile and link the app 

```bash
  gcc -o rapiKargo main.c helpers.c dataStructures.c -rdynamic $(pkg-config --cflags --libs gtk+-3.0)
```

#### 6. Run the executable

```bash
    chmod +x rapiKArgo
    ./rapiKargo
```

## User guide

#### 1.Register customers

<img src="https://github.com/WilmerCP/RapiKargo/blob/master/img/new_customer.png" width="500">

#### 2.Obtain customer ID from customer listing page

<img src="https://github.com/WilmerCP/RapiKargo/blob/master/img/customer_list.png" width="500">

#### 3.Create cargo for a specific user

<img src="https://github.com/WilmerCP/RapiKargo/blob/master/img/new_cargo.png" width="500">

#### 4. Manage the delivery process from cargo listing page

<img src="https://github.com/WilmerCP/RapiKargo/blob/master/img/manage_cargo.png" width="500">

#### 5. Check customer delivery history

<img src="https://github.com/WilmerCP/RapiKargo/blob/master/img/customer_history.png" width="500">

## License

This project is licensed under the MIT License.
