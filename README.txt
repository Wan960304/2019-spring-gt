## How to run
### Linux
```
# (Option) build libfakemn.a
$ cd fake-mininet && make lib && cd .. && cp fake-mininet/libfakemn.a .
# build
$ make 
# run 
$ ./main.out
#plot
$ dot -Tpng plot.dot -o graph.png
```




演算法(無向圖):

1.找出奇數degree點

2.所以奇數點彼此配對的，找出兩兩配對有最短的總路徑長的配對結果

3.兩兩奇數點相連進行補邊

4.以DFS走完所有補邊後的路徑



程式設計想法:

1.因選擇無向圖的問題，而此拓樸為有向，因此我將graph檔interpret後，利用elist中的資訊，將graph轉成無向的存至adjacency matrix中

2.利用adjacency matrix找出所有奇數degree點

3.以BFS找出所有兩兩奇數點間的最短路徑長，記錄在oddmap中

4.進行兩兩配對排列組合(利用遞迴)，利用oddmap找出最短的補邊總路徑長

5.將配對後的補邊路徑新增至adjacency matrix中

6.最後以總路徑長為條件，DFS找到結果



測試與結果:

圖輸入檔為:graph.txt

點至點連接，其為無向路徑

text1 input:

a b 
c a 
b c 
e b 
e c 
c d 
d e 



all vertex: a b c e d 

adjacency matrix:
  a b c e d 
a 0 1 1 0 0 
b 1 0 1 1 0 
c 1 1 0 1 1 
e 0 1 1 0 1 
d 0 0 1 1 0 

-------------------------------------------------------------
vertexs of odd degree: b e 

length of Shortest path between vertex: 
  b e 
b 0 1 
e 1 0 

minimum length of Increased path: 1
Pairing odd points: (b,e) 

adjacency matrix:
  a b c e d 
a 0 1 1 0 0 
b 1 0 1 2 0 
c 1 1 0 1 1 
e 0 2 1 0 1 
d 0 0 1 1 0 

-------------------------------------------------------------
result: 
a->b->c->e->b->e->d->c->a




text2 input(graph11.txt):

a b
a f
a g
b c
c e
c d
e d
e f
f g
d g
d h


-------------------------------------------------------------
all vertex: a b f g c e d h 

adjacency matrix:
  a b f g c e d h 
a 0 1 1 1 0 0 0 0 
b 1 0 0 0 1 0 0 0 
f 1 0 0 1 0 1 0 0 
g 1 0 1 0 0 0 1 0 
c 0 1 0 0 0 1 1 0 
e 0 0 1 0 1 0 1 0 
d 0 0 0 1 1 1 0 1 
h 0 0 0 0 0 0 1 0 

-------------------------------------------------------------
vertexs of odd degree: a f g c e h 

length of Shortest path between vertex: 
  a f g c e h 
a 0 1 1 2 2 3 
f 1 0 1 2 1 3 
g 1 1 0 2 2 2 
c 2 2 2 0 1 2 
e 2 1 2 1 0 2 
h 3 3 2 2 2 0 

minimum length of Increased path: 4
Pairing odd points: (a,f) (g,h) (c,e) 

adjacency matrix:
  a b f g c e d h 
a 0 1 2 1 0 0 0 0 
b 1 0 0 0 1 0 0 0 
f 2 0 0 1 0 1 0 0 
g 1 0 1 0 0 0 2 0 
c 0 1 0 0 0 2 1 0 
e 0 0 1 0 2 0 1 0 
d 0 0 0 2 1 1 0 2 
h 0 0 0 0 0 0 2 0 

-------------------------------------------------------------
result: 
a->b->c->e->f->a->f->g->d->c->e->d->h->d->g->a
