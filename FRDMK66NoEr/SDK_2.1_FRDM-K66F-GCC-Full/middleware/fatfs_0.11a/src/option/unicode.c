#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/fatfs_0.11a/src/ff.h"

#if _USE_LFN != 0

#if   _CODE_PAGE == 932	/* Japanese Shift_JIS */
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/fatfs_0.11a/src/option/cc932.c"
#elif _CODE_PAGE == 936	/* Simplified Chinese GBK */
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/fatfs_0.11a/src/option/cc936.c"
#elif _CODE_PAGE == 949	/* Korean */
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/fatfs_0.11a/src/option/cc949.c"
#elif _CODE_PAGE == 950	/* Traditional Chinese Big5 */
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/fatfs_0.11a/src/option/cc950.c"
#else					/* Single Byte Character-Set */
#include "../../../../../SDK_2.1_FRDM-K66F-GCC-Full/middleware/fatfs_0.11a/src/option/ccsbcs.c"
#endif

#endif
