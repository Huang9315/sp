參考ChatGPT

使用方法

1.確保安裝了C編譯器（如gcc）。

2.將您的源代碼保存到一個文件中（例如 input.txt）。

3.在終端中運行編譯器，並指定源文件作為命令行參數：
```
./compiler input.txt
```
功能
* 詞法分析：將源代碼轉換為標記序列，並顯示每個標記的類型。
* 語法分析：解析標記序列並生成對應的中間表示。
* 程式碼生成：根據中間表示生成目標代碼。

程式碼範例
input.txt
```
int main() {
    int x = 0;
    do {
        x++;
    } while (x < 5);
    return 0;
}
```
執行結果


```
token=int, type=Keyword

token=main, type=Id

token=(, type=Char

token=), type=Char

token={, type=Char

token=int, type=Keyword

token=x, type=Id

token==, type=Op

token=0, type=Int

token=;, type=Char

token=do, type=Keyword

token={, type=Char

token=x, type=Id

token=++, type=Op

token=;, type=Char

token=}, type=Char

token=while, type=Keyword

token=(, type=Char

token=x, type=Id

token=<, type=Op

token=5, type=Int

token=), type=Char

token=;, type=Char

token=return, type=Keyword

token=0, type=Int

token=;, type=Char

token=}, type=Char

========== dump ==============

0: int

1: main

2: (

3: )

4: {

5: int

6: x

7: =

8: 0

9: ;

10: do

11: {

12: x

13: ++

14: ;

15: }

16: while

17: (

18: x

19: <

20: 5

21: )

22: ;

23: return

24: 0

25: ;

26: }

```

注意事項:

1.目前該編譯器僅支持一個簡單的子集語言，並不支持所有C語言功能。
2.這只是一個教育性質的編譯器示例，可能無法處理複雜的代碼。
3.該編譯器中的錯誤處理機制有限，並且可能無法處理所有錯誤情況。
