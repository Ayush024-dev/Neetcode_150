## 2. When to Use It
Use a segment tree when:
- You have **frequent range queries**.
- You also need **frequent updates**.
- Constraints are large (n, q ~ 10^5 or more).
- The query operation is **mergeable** (associative):

```
sum([L,R]) = sum([L,M]) + sum([M+1,R])
max([L,R]) = max(max([L,M]), max([M+1,R]))
gcd([L,R]) = gcd(gcd([L,M]), gcd([M+1,R]))
```

## 3. "Spot It" Checklist
When reading a problem, tick these boxes:

1. **Range Queries?**  
 - "Find sum/min/max/gcd in [L, R]"
 - "Count numbers > k in [L, R]"

2. **Array Changes?**  
 - "Update index i to x" (point update)
 - "Add k to every element in [L, R]" (range update → lazy propagation)

3. **Large Constraints?**  
 - n ~ 10^5+
 - q ~ 10^5+

4. **Mergeable Operation?**  
 - Can be combined from subranges

5. **Prefix Sum / BIT not enough?**  
 - Need min/max queries with updates
 - Need multiple types of queries
 - Need range updates + range queries

✅ If **3 or more boxes are ticked**, strongly consider a segment tree.
