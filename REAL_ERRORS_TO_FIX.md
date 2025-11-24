# Real Compiler Errors That Need Fixing

## Date: November 24, 2025

## Issue #1: Struct Initializer List Not Supported ❌

### Error Location
**File:** `src/semantic.cpp` or `src/parser.y` (initializer handling)

### Error Message
```
Line 14: SEMANTIC ERROR: Incompatible types in initialization: cannot convert 'initializer_list<initializer_list<int>>' to 'Point'
```

### Test Case
```c
typedef struct {
    int x;
    int y;
} Point;

int main() {
    Point p1 = {1, 2};  // ❌ ERROR: Treated as nested initializer instead of flat struct
    return 0;
}
```

### Expected Behavior
The compiler should recognize `{1, 2}` as a flat initializer list for a struct with 2 int fields, not as a 2D nested list.

### Root Cause
The semantic analyzer is incorrectly interpreting `{1, 2}` as `initializer_list<initializer_list<int>>` (nested) instead of `initializer_list<int>` (flat).

### Files to Investigate
1. `src/semantic.cpp` - `check_initializer()` function
2. `src/parser.y` - Initializer list parsing rules
3. `src/ast.h` - InitializerList node structure

### Fix Strategy
1. Check how initializer lists are being parsed and stored in AST
2. Modify semantic checker to differentiate between:
   - Flat list for struct: `{1, 2}` → assign to x, y
   - Nested list for array: `{{1, 2}, {3, 4}}` → 2D array
3. Add logic to match initializer elements with struct members

---

## Issue #2: Uninitialized Array Variables Have Memory Issues (MAYBE NOT A BUG)

### Error Location
**File:** Possibly `src/mips.cpp` or `src/codegen.cpp` (stack allocation)

### Observation
Arrays declared without initializers may not have properly allocated/zeroed memory:
```c
int z[2][2];  // Declared but not initialized
z[0][0] = x[0][0] + y[0][0];  // Writing to uninitialized memory
```

### Test Results
- **Actually Works!** The element-wise addition test passes with output: `6 8 10 12` ✓
- This suggests memory allocation is working correctly

### Conclusion
This is likely **NOT A BUG**. The compiler correctly allocates stack space for uninitialized arrays. Previous test failures were likely due to:
1. Test case issues (not compiler bugs)
2. The register allocation bug (already fixed)

---

## Current Status Summary

### ✅ Already Fixed
1. **Register Allocation Bug** - Loop variables being overwritten
   - File: `src/mips.cpp`, function `allocate_saved_register()`
   - Status: RESOLVED ✓

### ❌ Needs Fixing
1. **Struct Initializer Lists** - Cannot use `{1, 2}` syntax for structs
   - Files: `src/semantic.cpp`, `src/parser.y`
   - Priority: HIGH
   - Impact: Common C programming pattern

### ✅ False Alarms (Not Bugs)
1. Element-wise array operations - Actually work correctly
2. Uninitialized array allocation - Works correctly
3. Nested loops with multiple arrays - Works correctly after register fix

---

## Action Items

### Priority 1: Fix Struct Initializers
**Goal:** Allow `Point p = {1, 2};` syntax

**Steps:**
1. Examine how parser handles initializer lists in `src/parser.y`
2. Check AST structure for InitializerList nodes
3. Modify `src/semantic.cpp` to handle flat struct initializers
4. Add test cases for:
   - Simple struct: `{1, 2}`
   - Nested struct: `{{1, 2}, 3}`
   - Array of structs: `{{1, 2}, {3, 4}}`

### Priority 2: Test Edge Cases
**Goal:** Verify all array and struct operations work

**Test Cases:**
- ✅ 2D arrays with nested initializers - WORKS
- ✅ Element-wise operations - WORKS
- ✅ Matrix operations - WORKS
- ❌ Struct with initializer list - FAILS
- ❌ Array of structs with initializers - Unknown

---

## Recommendation

**DO NOT modify test cases to work around compiler limitations!**

Instead:
1. Document the exact error
2. Identify the root cause in compiler code
3. Fix the compiler to support the feature
4. Verify fix with original test case

This ensures the compiler becomes more robust and feature-complete, rather than hiding bugs by simplifying tests.
