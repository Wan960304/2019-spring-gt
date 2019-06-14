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

圖輸入檔為:graph.txt
點至點連接，其為無向路徑
ex:
a b
c a
b c
e b
e c
c d
d e



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
