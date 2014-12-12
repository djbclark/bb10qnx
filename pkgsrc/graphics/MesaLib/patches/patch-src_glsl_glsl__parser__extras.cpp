$NetBSD$

--- src/glsl/glsl_parser_extras.cpp.orig	2011-10-15 00:43:58.000000000 +0000
+++ src/glsl/glsl_parser_extras.cpp
@@ -20,6 +20,9 @@
  * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  * DEALINGS IN THE SOFTWARE.
  */
+#ifdef __QNXNTO__
+#include <math.h> /* outside of extern "C"{} below */
+#endif
 #include <stdio.h>
 #include <stdarg.h>
 #include <string.h>
