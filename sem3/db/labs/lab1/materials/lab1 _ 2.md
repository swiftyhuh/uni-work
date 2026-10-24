<!-- page 1 -->
# _<u>Create tables</u>_

We want to implement a system that keeps information about teas and shops. Each shop is characterized by name, city, number of shops, number of clients and one manager. Each tea is characterized by name, quantity, price and type.  The type has a type name and a number of teas that can be included there. In a type there are 1 or more teas. A tea can be find in 1 or more shops and in a a shop one can find 1 or more teas. A manager has a name and an experience. A shop has only one manager and a manager works for only one shop.

```
Createdatabase TeaShops
go
use TeaShops
go
```

```
CREATETABLE Shops
(Pid INTPRIMARYKEYIDENTITY,
Namevarchar(50),
City varchar(50)NOTNULL,
NoOfShops int,
NoOfClients int)
```

```
CREATETABLE TeaTypes
(SidINTPRIMARYKEYIDENTITY,
Typevarchar(50)DEFAULT'Mint',
NoOfTeas int)
```

```
CREATETABLE Teas
(Cid INTPRIMARYKEYIDENTITY,
Namevarchar(50),
Quantity intCHECK (Quantity=1 OR Quantity=2),
Price int,
SidintFOREIGNKEYREFERENCES TeaTypes(Sid))
```

```
CREATETABLE ShopsTeas
(Cid INTFOREIGNKEYREFERENCES Teas(Cid),
Pid INTFOREIGNKEYREFERENCES Shops(Pid),
```

1

<!-- page 2 -->
```
CONSTRAINT pk_Teas PRIMARYKEY (Cid, Pid)
)
```

```
CREATETABLE Managers
```

```
(Mid INTFOREIGNKEYREFERENCES Shops(Pid),
Namevarchar(50)NOTNULL,
Experience INT,
CONSTRAINT pk_ShopsManagers PRIMARYKEY(Mid)
)
```

- `-- DROP DATABASE TeaShops`

2
