//
// Created by Ellen7ions on 2021/9/3.
//

#ifndef GEMINISIM_UTILS_H
#define GEMINISIM_UTILS_H

#define L_SHIFT(X, L)   (X << L)
#define R_SHIFT(X, R)   (X >> R)
#define SLICE_OP(X)     (R_SHIFT(X, 26) & 0B111111)
#define SLICE_FUNC(X)   (R_SHIFT(X, 0) & 0B111111)
#define SLICE_RS(X)     (R_SHIFT(X, 21) & 0B11111)
#define SLICE_RT(X)     (R_SHIFT(X, 16) & 0B11111)
#define SLICE_RD(X)     (R_SHIFT(X, 11) & 0B11111)
#define SLICE_IMME(X)   (R_SHIFT(L_SHIFT(X, 16), 16))

#endif //GEMINISIM_UTILS_H
