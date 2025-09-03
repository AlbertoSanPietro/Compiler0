/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"

extern int yylex(void);
extern int yyparse(void);
void yyerror(const char *s) { fprintf(stderr, "Parse error: %s\n", s); exit(1); }

#line 81 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_MAIN = 4,                       /* MAIN  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_NEQ = 10,                       /* NEQ  */
  YYSYMBOL_LE = 11,                        /* LE  */
  YYSYMBOL_GE = 12,                        /* GE  */
  YYSYMBOL_LT = 13,                        /* LT  */
  YYSYMBOL_GT = 14,                        /* GT  */
  YYSYMBOL_LSHIFT = 15,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 16,                    /* RSHIFT  */
  YYSYMBOL_AND = 17,                       /* AND  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_XOR = 19,                       /* XOR  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_VOID = 21,                      /* VOID  */
  YYSYMBOL_ANDAND = 22,                    /* ANDAND  */
  YYSYMBOL_OROR = 23,                      /* OROR  */
  YYSYMBOL_LNOT = 24,                      /* LNOT  */
  YYSYMBOL_NUMBER = 25,                    /* NUMBER  */
  YYSYMBOL_IDENT = 26,                     /* IDENT  */
  YYSYMBOL_27_ = 27,                       /* '+'  */
  YYSYMBOL_28_ = 28,                       /* '-'  */
  YYSYMBOL_29_ = 29,                       /* '*'  */
  YYSYMBOL_30_ = 30,                       /* '/'  */
  YYSYMBOL_31_ = 31,                       /* '%'  */
  YYSYMBOL_UMINUS = 32,                    /* UMINUS  */
  YYSYMBOL_UNOT = 33,                      /* UNOT  */
  YYSYMBOL_LOWER_THAN_ELSE = 34,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* ')'  */
  YYSYMBOL_37_ = 37,                       /* '{'  */
  YYSYMBOL_38_ = 38,                       /* '}'  */
  YYSYMBOL_39_ = 39,                       /* ','  */
  YYSYMBOL_40_ = 40,                       /* ';'  */
  YYSYMBOL_41_ = 41,                       /* '='  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_Program = 43,                   /* Program  */
  YYSYMBOL_Function = 44,                  /* Function  */
  YYSYMBOL_ParamListOpt = 45,              /* ParamListOpt  */
  YYSYMBOL_ParamList = 46,                 /* ParamList  */
  YYSYMBOL_BlockItemList = 47,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 48,                 /* BlockItem  */
  YYSYMBOL_Decl = 49,                      /* Decl  */
  YYSYMBOL_Stmt = 50,                      /* Stmt  */
  YYSYMBOL_ArgListOpt = 51,                /* ArgListOpt  */
  YYSYMBOL_ArgList = 52,                   /* ArgList  */
  YYSYMBOL_Expr = 53                       /* Expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   453

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    31,     2,     2,
      35,    36,    29,    27,    39,    28,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
       2,    41,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    51,    51,    52,    56,    57,    58,    62,    63,    64,
      68,    69,    73,    74,    78,    79,    83,    84,    88,    89,
      90,    91,    92,    93,    94,    95,    99,   100,   104,   105,
     109,   110,   111,   113,   114,   115,   116,   117,   119,   120,
     121,   122,   123,   124,   126,   127,   128,   129,   130,   131,
     133,   134,   135,   137,   138
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "MAIN", "IF",
  "ELSE", "WHILE", "RETURN", "EQ", "NEQ", "LE", "GE", "LT", "GT", "LSHIFT",
  "RSHIFT", "AND", "OR", "XOR", "NOT", "VOID", "ANDAND", "OROR", "LNOT",
  "NUMBER", "IDENT", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS", "UNOT",
  "LOWER_THAN_ELSE", "'('", "')'", "'{'", "'}'", "','", "';'", "'='",
  "$accept", "Program", "Function", "ParamListOpt", "ParamList",
  "BlockItemList", "BlockItem", "Decl", "Stmt", "ArgListOpt", "ArgList",
  "Expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,     4,   -22,     7,   -69,   -19,   -16,   -12,   -69,   -69,
       6,     6,     6,    32,   -69,    26,    25,    31,    33,   -69,
      34,    73,    37,    51,    72,    66,    72,    72,    67,    59,
      69,    86,   -20,    72,    -2,   -69,   -69,   -69,   -69,    52,
      58,    -9,   413,   413,   413,   413,   -69,    70,   413,   413,
     -69,   121,   413,   413,    65,   -69,   -69,   -69,   -69,   -69,
     413,   217,   245,   -69,   -69,   413,   -69,   273,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   -69,    77,    68,   301,
     153,   -69,   185,    92,    92,    81,   -69,   391,   391,   401,
     401,   401,   401,   422,   422,   370,   324,   347,   -69,    97,
      93,    93,    11,    11,    11,    80,   413,   -69,   -69,   102,
     -69,   -69,   -69,   301,    92,   -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     0,     0,     0,     1,     3,
       7,     7,     7,     0,     9,     0,     8,     0,     0,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,    14,    15,    11,     0,
       0,     0,     0,     0,     0,     0,    30,    31,     0,     0,
      24,     0,    26,     0,     0,     4,    13,     5,     6,    16,
       0,     0,     0,    49,    52,    26,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    23,     0,    27,    28,
       0,    25,     0,     0,     0,     0,    54,    38,    39,    41,
      43,    40,    42,    47,    48,    44,    45,    46,    50,    51,
      33,    34,    35,    36,    37,     0,     0,    18,    17,    20,
      22,    32,    19,    29,     0,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -69,   -69,   122,    71,   -69,   120,    47,   -69,   -68,    62,
     -69,   -31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,    15,    16,    34,    35,    36,    37,    87,
      88,    89
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      51,    28,     1,    29,     7,    30,    31,     8,     5,    13,
       1,    61,    62,    63,    64,    52,    10,    66,    67,    11,
       2,    53,    90,    12,    32,   119,   120,    14,     2,    92,
       6,    59,    60,    79,    80,    33,    55,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    28,   125,    29,    19,    30,
      31,    28,    20,    29,    21,    30,    31,    22,    28,    23,
      29,    24,    30,    31,    26,    28,    25,    29,    32,    30,
      31,    56,    17,    18,    32,   123,    56,    56,    27,    33,
      57,    32,    38,    41,    42,    33,    58,    29,    32,    30,
      31,    56,    33,    91,    43,    65,    44,   116,   124,    33,
      45,    46,    47,   115,    48,    79,    80,   121,    32,    79,
     122,    49,    83,    84,    85,     9,    50,    95,     0,    33,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,     0,    39,    40,    81,    82,
      83,    84,    85,    54,     0,     0,     0,     0,     0,     0,
       0,    86,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,     0,     0,     0,
      81,    82,    83,    84,    85,     0,     0,     0,     0,     0,
       0,     0,     0,   117,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,     0,
       0,     0,    81,    82,    83,    84,    85,     0,     0,     0,
       0,     0,     0,     0,     0,   118,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,     0,     0,     0,    81,    82,    83,    84,    85,     0,
       0,     0,     0,    93,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,     0,
       0,     0,    81,    82,    83,    84,    85,     0,     0,     0,
       0,    94,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,     0,     0,     0,
      81,    82,    83,    84,    85,     0,     0,     0,     0,    96,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,     0,     0,     0,    81,    82,
      83,    84,    85,    68,    69,    70,    71,    72,    73,    74,
      75,    76,     0,    78,     0,     0,    79,    80,     0,     0,
       0,    81,    82,    83,    84,    85,    68,    69,    70,    71,
      72,    73,    74,    75,    76,     0,     0,     0,     0,    79,
      80,     0,     0,     0,    81,    82,    83,    84,    85,    68,
      69,    70,    71,    72,    73,    74,    75,     0,     0,     0,
       0,     0,    79,    80,     0,     0,     0,    81,    82,    83,
      84,    85,    70,    71,    72,    73,    74,    75,     0,     0,
       0,     0,     0,    79,    80,     0,    74,    75,    81,    82,
      83,    84,    85,    79,    80,     0,     0,     0,    81,    82,
      83,    84,    85,    44,     0,     0,     0,    45,    46,    47,
       0,    48,     0,     0,    79,    80,     0,     0,    49,    81,
      82,    83,    84,    85
};

static const yytype_int8 yycheck[] =
{
      31,     3,     3,     5,    26,     7,     8,     0,     4,     3,
       3,    42,    43,    44,    45,    35,    35,    48,    49,    35,
      21,    41,    53,    35,    26,    93,    94,    21,    21,    60,
      26,    40,    41,    22,    23,    37,    38,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,     3,   124,     5,    26,     7,
       8,     3,    36,     5,    39,     7,     8,    36,     3,    36,
       5,    37,     7,     8,    37,     3,     3,     5,    26,     7,
       8,    34,    11,    12,    26,   116,    39,    40,    37,    37,
      38,    26,    26,    26,    35,    37,    38,     5,    26,     7,
       8,    54,    37,    38,    35,    35,    20,    39,     6,    37,
      24,    25,    26,    36,    28,    22,    23,    36,    26,    22,
      40,    35,    29,    30,    31,     3,    40,    65,    -1,    37,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    26,    27,    27,    28,
      29,    30,    31,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    -1,    -1,    22,
      23,    -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    36,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      -1,    -1,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    36,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    -1,    -1,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    36,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    -1,    -1,    27,    28,
      29,    30,    31,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    19,    -1,    -1,    22,    23,    -1,    -1,
      -1,    27,    28,    29,    30,    31,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    22,
      23,    -1,    -1,    -1,    27,    28,    29,    30,    31,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,    -1,    22,    23,    -1,    -1,    -1,    27,    28,    29,
      30,    31,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    22,    23,    -1,    15,    16,    27,    28,
      29,    30,    31,    22,    23,    -1,    -1,    -1,    27,    28,
      29,    30,    31,    20,    -1,    -1,    -1,    24,    25,    26,
      -1,    28,    -1,    -1,    22,    23,    -1,    -1,    35,    27,
      28,    29,    30,    31
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    21,    43,    44,     4,    26,    26,     0,    44,
      35,    35,    35,     3,    21,    45,    46,    45,    45,    26,
      36,    39,    36,    36,    37,     3,    37,    37,     3,     5,
       7,     8,    26,    37,    47,    48,    49,    50,    26,    47,
      47,    26,    35,    35,    20,    24,    25,    26,    28,    35,
      40,    53,    35,    41,    47,    38,    48,    38,    38,    40,
      41,    53,    53,    53,    53,    35,    53,    53,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    22,
      23,    27,    28,    29,    30,    31,    40,    51,    52,    53,
      53,    38,    53,    36,    36,    51,    36,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    36,    39,    40,    40,    50,
      50,    36,    40,    53,     6,    50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    43,    43,    44,    44,    44,    45,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      50,    50,    50,    50,    50,    50,    51,    51,    52,    52,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     8,     8,     8,     0,     1,     1,
       2,     4,     1,     2,     1,     1,     3,     5,     4,     5,
       5,     7,     5,     3,     2,     3,     0,     1,     1,     3,
       1,     1,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     2,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Function  */
#line 51 "parser.y"
                                       { (yyval.node) = (yyvsp[0].node); generate_code((yyvsp[0].node)); }
#line 1259 "parser.tab.c"
    break;

  case 3: /* Program: Program Function  */
#line 52 "parser.y"
                                       { (yyval.node) = (yyvsp[0].node); generate_code((yyvsp[0].node)); }
#line 1265 "parser.tab.c"
    break;

  case 4: /* Function: INT MAIN '(' ParamListOpt ')' '{' BlockItemList '}'  */
#line 56 "parser.y"
                                                            { (yyval.node) = make_function("main", (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1271 "parser.tab.c"
    break;

  case 5: /* Function: INT IDENT '(' ParamListOpt ')' '{' BlockItemList '}'  */
#line 57 "parser.y"
                                                            { (yyval.node) = make_function((yyvsp[-6].sval), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1277 "parser.tab.c"
    break;

  case 6: /* Function: VOID IDENT '(' ParamListOpt ')' '{' BlockItemList '}'  */
#line 58 "parser.y"
                                                            { (yyval.node) = make_function((yyvsp[-6].sval), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1283 "parser.tab.c"
    break;

  case 7: /* ParamListOpt: %empty  */
#line 62 "parser.y"
                                       { (yyval.node) = NULL; }
#line 1289 "parser.tab.c"
    break;

  case 8: /* ParamListOpt: ParamList  */
#line 63 "parser.y"
                                       { (yyval.node) = (yyvsp[0].node); }
#line 1295 "parser.tab.c"
    break;

  case 9: /* ParamListOpt: VOID  */
#line 64 "parser.y"
                                       { (yyval.node) = NULL; }
#line 1301 "parser.tab.c"
    break;

  case 10: /* ParamList: INT IDENT  */
#line 68 "parser.y"
                                       { (yyval.node) = make_param_list(NULL, make_var_decl((yyvsp[0].sval), NULL)); }
#line 1307 "parser.tab.c"
    break;

  case 11: /* ParamList: ParamList ',' INT IDENT  */
#line 69 "parser.y"
                                      { (yyval.node) = make_param_list((yyvsp[-3].node), make_var_decl((yyvsp[0].sval), NULL)); }
#line 1313 "parser.tab.c"
    break;

  case 12: /* BlockItemList: BlockItem  */
#line 73 "parser.y"
                                       { (yyval.node) = make_stmt_list(NULL, (yyvsp[0].node)); }
#line 1319 "parser.tab.c"
    break;

  case 13: /* BlockItemList: BlockItemList BlockItem  */
#line 74 "parser.y"
                                       { (yyval.node) = make_stmt_list((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1325 "parser.tab.c"
    break;

  case 14: /* BlockItem: Decl  */
#line 78 "parser.y"
                                       { (yyval.node) = (yyvsp[0].node); }
#line 1331 "parser.tab.c"
    break;

  case 15: /* BlockItem: Stmt  */
#line 79 "parser.y"
                                       { (yyval.node) = (yyvsp[0].node); }
#line 1337 "parser.tab.c"
    break;

  case 16: /* Decl: INT IDENT ';'  */
#line 83 "parser.y"
                                       { (yyval.node) = make_var_decl((yyvsp[-1].sval), NULL); }
#line 1343 "parser.tab.c"
    break;

  case 17: /* Decl: INT IDENT '=' Expr ';'  */
#line 84 "parser.y"
                                      { (yyval.node) = make_var_decl((yyvsp[-3].sval), (yyvsp[-1].node)); }
#line 1349 "parser.tab.c"
    break;

  case 18: /* Stmt: IDENT '=' Expr ';'  */
#line 88 "parser.y"
                                      { (yyval.node) = make_assignment((yyvsp[-3].sval), (yyvsp[-1].node)); }
#line 1355 "parser.tab.c"
    break;

  case 19: /* Stmt: IDENT '(' ArgListOpt ')' ';'  */
#line 89 "parser.y"
                                      { (yyval.node) = make_function_call((yyvsp[-4].sval), (yyvsp[-2].node)); }
#line 1361 "parser.tab.c"
    break;

  case 20: /* Stmt: IF '(' Expr ')' Stmt  */
#line 90 "parser.y"
                                                 { (yyval.node) = make_if((yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1367 "parser.tab.c"
    break;

  case 21: /* Stmt: IF '(' Expr ')' Stmt ELSE Stmt  */
#line 91 "parser.y"
                                      { (yyval.node) = make_if((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1373 "parser.tab.c"
    break;

  case 22: /* Stmt: WHILE '(' Expr ')' Stmt  */
#line 92 "parser.y"
                                      { (yyval.node) = make_while((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1379 "parser.tab.c"
    break;

  case 23: /* Stmt: RETURN Expr ';'  */
#line 93 "parser.y"
                                      { (yyval.node) = make_return((yyvsp[-1].node)); }
#line 1385 "parser.tab.c"
    break;

  case 24: /* Stmt: RETURN ';'  */
#line 94 "parser.y"
                                      { (yyval.node) = make_return(NULL); }
#line 1391 "parser.tab.c"
    break;

  case 25: /* Stmt: '{' BlockItemList '}'  */
#line 95 "parser.y"
                                      { (yyval.node) = (yyvsp[-1].node); }
#line 1397 "parser.tab.c"
    break;

  case 26: /* ArgListOpt: %empty  */
#line 99 "parser.y"
                                      { (yyval.node) = NULL; }
#line 1403 "parser.tab.c"
    break;

  case 27: /* ArgListOpt: ArgList  */
#line 100 "parser.y"
                                      { (yyval.node) = (yyvsp[0].node); }
#line 1409 "parser.tab.c"
    break;

  case 28: /* ArgList: Expr  */
#line 104 "parser.y"
                                       { (yyval.node) = make_expr_list(NULL, (yyvsp[0].node)); }
#line 1415 "parser.tab.c"
    break;

  case 29: /* ArgList: ArgList ',' Expr  */
#line 105 "parser.y"
                                       { (yyval.node) = make_expr_list((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1421 "parser.tab.c"
    break;

  case 30: /* Expr: NUMBER  */
#line 109 "parser.y"
                                       { (yyval.node) = make_number((yyvsp[0].ival)); }
#line 1427 "parser.tab.c"
    break;

  case 31: /* Expr: IDENT  */
#line 110 "parser.y"
                                       { (yyval.node) = make_variable((yyvsp[0].sval)); }
#line 1433 "parser.tab.c"
    break;

  case 32: /* Expr: IDENT '(' ArgListOpt ')'  */
#line 111 "parser.y"
                                       { (yyval.node) = make_function_call((yyvsp[-3].sval), (yyvsp[-1].node)); }
#line 1439 "parser.tab.c"
    break;

  case 33: /* Expr: Expr '+' Expr  */
#line 113 "parser.y"
                                       { (yyval.node) = make_binop("+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1445 "parser.tab.c"
    break;

  case 34: /* Expr: Expr '-' Expr  */
#line 114 "parser.y"
                                       { (yyval.node) = make_binop("-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1451 "parser.tab.c"
    break;

  case 35: /* Expr: Expr '*' Expr  */
#line 115 "parser.y"
                                       { (yyval.node) = make_binop("*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1457 "parser.tab.c"
    break;

  case 36: /* Expr: Expr '/' Expr  */
#line 116 "parser.y"
                                       { (yyval.node) = make_binop("/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1463 "parser.tab.c"
    break;

  case 37: /* Expr: Expr '%' Expr  */
#line 117 "parser.y"
                                       { (yyval.node) = make_binop("%", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1469 "parser.tab.c"
    break;

  case 38: /* Expr: Expr EQ Expr  */
#line 119 "parser.y"
                                       { (yyval.node) = make_binop("==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1475 "parser.tab.c"
    break;

  case 39: /* Expr: Expr NEQ Expr  */
#line 120 "parser.y"
                                       { (yyval.node) = make_binop("!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1481 "parser.tab.c"
    break;

  case 40: /* Expr: Expr LT Expr  */
#line 121 "parser.y"
                                       { (yyval.node) = make_binop("<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1487 "parser.tab.c"
    break;

  case 41: /* Expr: Expr LE Expr  */
#line 122 "parser.y"
                                       { (yyval.node) = make_binop("<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1493 "parser.tab.c"
    break;

  case 42: /* Expr: Expr GT Expr  */
#line 123 "parser.y"
                                       { (yyval.node) = make_binop(">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1499 "parser.tab.c"
    break;

  case 43: /* Expr: Expr GE Expr  */
#line 124 "parser.y"
                                       { (yyval.node) = make_binop(">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1505 "parser.tab.c"
    break;

  case 44: /* Expr: Expr AND Expr  */
#line 126 "parser.y"
                                       { (yyval.node) = make_binop("&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1511 "parser.tab.c"
    break;

  case 45: /* Expr: Expr OR Expr  */
#line 127 "parser.y"
                                       { (yyval.node) = make_binop("|", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1517 "parser.tab.c"
    break;

  case 46: /* Expr: Expr XOR Expr  */
#line 128 "parser.y"
                                       { (yyval.node) = make_binop("^", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1523 "parser.tab.c"
    break;

  case 47: /* Expr: Expr LSHIFT Expr  */
#line 129 "parser.y"
                                       { (yyval.node) = make_binop("<<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1529 "parser.tab.c"
    break;

  case 48: /* Expr: Expr RSHIFT Expr  */
#line 130 "parser.y"
                                       { (yyval.node) = make_binop(">>", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1535 "parser.tab.c"
    break;

  case 49: /* Expr: NOT Expr  */
#line 131 "parser.y"
                                       { (yyval.node) = make_unaryop("~", (yyvsp[0].node)); }
#line 1541 "parser.tab.c"
    break;

  case 50: /* Expr: Expr ANDAND Expr  */
#line 133 "parser.y"
                                       { (yyval.node) = make_binop("&&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1547 "parser.tab.c"
    break;

  case 51: /* Expr: Expr OROR Expr  */
#line 134 "parser.y"
                                       { (yyval.node) = make_binop("||", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1553 "parser.tab.c"
    break;

  case 52: /* Expr: LNOT Expr  */
#line 135 "parser.y"
                                       { (yyval.node) = make_unaryop("!", (yyvsp[0].node)); }
#line 1559 "parser.tab.c"
    break;

  case 53: /* Expr: '-' Expr  */
#line 137 "parser.y"
                                       { (yyval.node) = make_unaryop("-", (yyvsp[0].node)); }
#line 1565 "parser.tab.c"
    break;

  case 54: /* Expr: '(' Expr ')'  */
#line 138 "parser.y"
                                       { (yyval.node) = (yyvsp[-1].node); }
#line 1571 "parser.tab.c"
    break;


#line 1575 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 141 "parser.y"


