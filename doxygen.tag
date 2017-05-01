<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>byte_code.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/</path>
    <filename>d3/d98/byte__code_8c</filename>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">utils/link_list.h</includes>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">utils/symbol_table.h</includes>
    <includes id="d4/da2/parsing__tree_8h" name="parsing_tree.h" local="yes" imported="no">utils/parsing_tree.h</includes>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">utils/error.h</includes>
    <includes id="d7/d6f/byte__code_8h" name="byte_code.h" local="yes" imported="no">byte_code.h</includes>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>handle_if_stmt_helper</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a2c6d22bf71c438b047ef27cac65b3e10</anchor>
      <arglist>(parsing_tree_st *then_node)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>byte_code_new</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>ab0d886eb3f5d4e1f073e19b0ef6de39c</anchor>
      <arglist>(link_list_st *, char *, char *, char *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>handle_stmt_list</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a6ae2a7389362c4f7141f04fed77b5537</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>handle_stmt</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a6213e8dd571241fb54d0b30c6924818a</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char *</type>
      <name>handle_boolean_value</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a7fe613f397d34cca19c4e24c2d6630e0</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char *</type>
      <name>handle_boolean_expr</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a45a4929d8c3c287205242bfa9b2c82b6</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>handle_if_stmt</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a6883b078f5dc3b58ebc46d4612cc4991</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>handle_for_stmt</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>afb69989a7e48f895ab461b4bf76e3aef</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char *</type>
      <name>handle_expr</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a07bf04e321785eb437137257f0210d3e</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char *</type>
      <name>handle_term</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a5ab926fa2d7216cb925d14f30f0c538e</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>handle_decl_stmt</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>ab08c37cde3d4379c0afe754e2a7b8c4c</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>handle_assign_stmt</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a5de82e593c7f4cb1e7939a49438fa3c0</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>handle_print_stmt</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a09e01fef02b693f938afe237ef83e223</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char *</type>
      <name>handle_res1</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a77a3a12c30e6e016a971d6e0140b5d30</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code, char *terms_data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char *</type>
      <name>handle_factor</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a59e1027eda2ce3b0d9d1f3cede5480f2</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static char *</type>
      <name>handle_res2</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a9b9e51554a0bcb25a6671f6bb85364a6</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, link_list_st *byte_code, char *factors_data)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_digits_num</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a675863d33fa107ac27d4ef44a52f295e</anchor>
      <arglist>(int int_num)</arglist>
    </member>
    <member kind="function">
      <type>link_list_st *</type>
      <name>semantic_analysis</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a26cceb1e7c00b9df7c4f71c9205e4137</anchor>
      <arglist>(parsing_tree_st *parsing_tree_node, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>temp_id</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>acac08054e479d3ae527719e4e62a140b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>loop_id</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a3a6355a00e74fcb5ef6ef305c0f63d15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>if_id</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>ac6938a23f24a35cdc277ea1139e67d4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static int</type>
      <name>else_id</name>
      <anchorfile>d3/d98/byte__code_8c.html</anchorfile>
      <anchor>a4d9adc45272f1ea9d4fb6c40a11f15d7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>byte_code.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/</path>
    <filename>d7/d6f/byte__code_8h</filename>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">utils/link_list.h</includes>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">utils/symbol_table.h</includes>
    <includes id="d4/da2/parsing__tree_8h" name="parsing_tree.h" local="yes" imported="no">utils/parsing_tree.h</includes>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">utils/error.h</includes>
    <member kind="function">
      <type>link_list_st *</type>
      <name>semantic_analysis</name>
      <anchorfile>d7/d6f/byte__code_8h.html</anchorfile>
      <anchor>a291551985e8ffdd760a447eda97e836c</anchor>
      <arglist>(parsing_tree_st *, symbol_table_st *)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>compiler.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/</path>
    <filename>d6/d0e/compiler_8c</filename>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">utils/link_list.h</includes>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">utils/symbol_table.h</includes>
    <includes id="d4/da2/parsing__tree_8h" name="parsing_tree.h" local="yes" imported="no">utils/parsing_tree.h</includes>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">utils/error.h</includes>
    <includes id="db/db7/lexical_8h" name="lexical.h" local="yes" imported="no">lexical.h</includes>
    <includes id="d5/d36/parser_8h" name="parser.h" local="yes" imported="no">parser.h</includes>
    <includes id="d7/d6f/byte__code_8h" name="byte_code.h" local="yes" imported="no">byte_code.h</includes>
    <member kind="function">
      <type>int</type>
      <name>print_byte_code</name>
      <anchorfile>d6/d0e/compiler_8c.html</anchorfile>
      <anchor>ac9b122fddf97bec0ab26249144dc60c2</anchor>
      <arglist>(link_node_st *node, void *cb_data)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>s_usage</name>
      <anchorfile>d6/d0e/compiler_8c.html</anchorfile>
      <anchor>af52a5d5ea91424c6e657b417d4ffd515</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>d6/d0e/compiler_8c.html</anchorfile>
      <anchor>a0ddf1224851353fc92bfbff6f499fa97</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>lexical.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/</path>
    <filename>dd/d3a/lexical_8c</filename>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">./utils/error.h</includes>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">./utils/symbol_table.h</includes>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">./utils/link_list.h</includes>
    <includes id="d9/d56/link__node_8h" name="link_node.h" local="yes" imported="no">./utils/link_node.h</includes>
    <includes id="db/db7/lexical_8h" name="lexical.h" local="yes" imported="no">lexical.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_TOKEN_BUFF_SIZE</name>
      <anchorfile>dd/d3a/lexical_8c.html</anchorfile>
      <anchor>a4d7ba03b2c051b4ff653ae66ee84aae9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ENLARGE_FACTOR</name>
      <anchorfile>dd/d3a/lexical_8c.html</anchorfile>
      <anchor>a59e33ec07bb1a561dc763265eee3c3a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>emit_token</name>
      <anchorfile>dd/d3a/lexical_8c.html</anchorfile>
      <anchor>a98cdc5d08f56049c0930f8c060ded995</anchor>
      <arglist>(link_list_st *token_list, char *token_buff)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>emit_error</name>
      <anchorfile>dd/d3a/lexical_8c.html</anchorfile>
      <anchor>a800628b3e69280a93895fa0d22c80f08</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>link_list_st *</type>
      <name>lexical_analysis</name>
      <anchorfile>dd/d3a/lexical_8c.html</anchorfile>
      <anchor>a568f1f60a2920002698ac69be4944f5d</anchor>
      <arglist>(symbol_table_st *symbol_table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>lexical.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/</path>
    <filename>db/db7/lexical_8h</filename>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">utils/symbol_table.h</includes>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">utils/link_list.h</includes>
    <member kind="function">
      <type>link_list_st *</type>
      <name>lexical_analysis</name>
      <anchorfile>db/db7/lexical_8h.html</anchorfile>
      <anchor>a568f1f60a2920002698ac69be4944f5d</anchor>
      <arglist>(symbol_table_st *symbol_table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>parser.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/</path>
    <filename>d2/d72/parser_8c</filename>
    <includes id="d4/da2/parsing__tree_8h" name="parsing_tree.h" local="yes" imported="no">utils/parsing_tree.h</includes>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">utils/symbol_table.h</includes>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">utils/link_list.h</includes>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>raise_syntax_error</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a5afa8f9a59e34d49e576f8fdcf75fafb</anchor>
      <arglist>(int line_no, char *msg)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_decl_stmt</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a042327c49734c1689c2248ac0852ea98</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_print_stmt</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a8fa6afdbb8fdfed41c09a520a6e053e3</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_assign_stmt</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a6cb0e671e5723a77bd96a1742dc5f1a7</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_if_stmt</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a48ff657064a46d6baa13810a58870a3f</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_for_stmt</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>afe9c33802a8266ee6c51322f8af6d764</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_expre</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>ab97e66f225eb9d9927106a4d6dce826c</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_term</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>af1a942f5b8cfd9f350820c10f7c83ce2</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_factor</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a8c6714cfd53cf878c5b159118e798b89</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_res1</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a7a80e4875a816566ba25c4675205984d</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_res2</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a4dee366c58c91c5901f70ffc17f77582</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_stmt</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a0edf34a03424770d85ce26b1d9f63c87</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_boolean_expre</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a2246902f34d06354d4eccefaaf2ba30d</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_boolean_value</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>af6ae37ab560b122151889b568ac0aef7</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static parsing_tree_st *</type>
      <name>generate_stmt_list</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>ac19b2f11c205d05ad339b85b3b09c457</anchor>
      <arglist>(link_list_st *, symbol_table_st *)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>syntax_analysis</name>
      <anchorfile>d2/d72/parser_8c.html</anchorfile>
      <anchor>a5adfc0ce13d259b16d78749025cd4535</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>parser.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/</path>
    <filename>d5/d36/parser_8h</filename>
    <includes id="d4/da2/parsing__tree_8h" name="parsing_tree.h" local="yes" imported="no">utils/parsing_tree.h</includes>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">utils/symbol_table.h</includes>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">utils/link_list.h</includes>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>syntax_analysis</name>
      <anchorfile>d5/d36/parser_8h.html</anchorfile>
      <anchor>a5adfc0ce13d259b16d78749025cd4535</anchor>
      <arglist>(link_list_st *token_list, symbol_table_st *symbol_table)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>error.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>db/dcc/error_8c</filename>
    <member kind="function">
      <type>void</type>
      <name>error_msg</name>
      <anchorfile>db/dcc/error_8c.html</anchorfile>
      <anchor>abf28cef257b6ba9a5225cd0043767d41</anchor>
      <arglist>(int lineno, char *msg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error_errno</name>
      <anchorfile>db/dcc/error_8c.html</anchorfile>
      <anchor>a6ad6cfd4514d40fb69948abdfcc24938</anchor>
      <arglist>(int error_number)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>error.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>da/d41/error_8h</filename>
    <member kind="function">
      <type>void</type>
      <name>error_msg</name>
      <anchorfile>da/d41/error_8h.html</anchorfile>
      <anchor>a622e3996caaecda3cc2f1fa7443968d3</anchor>
      <arglist>(int, char *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>error_errno</name>
      <anchorfile>da/d41/error_8h.html</anchorfile>
      <anchor>a4ba169d09dde3a6e125854e4af2e0859</anchor>
      <arglist>(int)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>link_list.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>de/dec/link__list_8c</filename>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">error.h</includes>
    <includes id="d9/d56/link__node_8h" name="link_node.h" local="yes" imported="no">link_node.h</includes>
    <includes id="d4/d51/link__list_8h" name="link_list.h" local="yes" imported="no">link_list.h</includes>
    <class kind="struct">link_list</class>
    <member kind="function">
      <type>link_list_st *</type>
      <name>link_list_init</name>
      <anchorfile>de/dec/link__list_8c.html</anchorfile>
      <anchor>a2aaabdf1ce440e05e148e1f9ff3b4084</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>link_list_free</name>
      <anchorfile>de/dec/link__list_8c.html</anchorfile>
      <anchor>a2a6c90057b3c053ee5cfdb796bf4b7c0</anchor>
      <arglist>(link_list_st *list)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_list_pop</name>
      <anchorfile>de/dec/link__list_8c.html</anchorfile>
      <anchor>af189a40a196e887275c1040b79a718e9</anchor>
      <arglist>(link_list_st *list)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_list_top</name>
      <anchorfile>de/dec/link__list_8c.html</anchorfile>
      <anchor>ac97407c5bddcc532f2468490b0d54957</anchor>
      <arglist>(link_list_st *list)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_list_append</name>
      <anchorfile>de/dec/link__list_8c.html</anchorfile>
      <anchor>afa796d513765c882ad048d06976f09db</anchor>
      <arglist>(link_list_st *list, link_node_st *node)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>link_list_traverse</name>
      <anchorfile>de/dec/link__list_8c.html</anchorfile>
      <anchor>a2b491d06b7635733b2b2c3de83cd29b7</anchor>
      <arglist>(link_list_st *list, cb_func callback, void *cb_data)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>link_list.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>d4/d51/link__list_8h</filename>
    <includes id="d9/d56/link__node_8h" name="link_node.h" local="yes" imported="no">link_node.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>LINK_LIST_CONTINUE</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>a825fd1d8db90478e0e8e4cb2346d40c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LINK_LIST_STOP</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>a21109554c8217234065c7bd387c4855f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct link_list</type>
      <name>link_list_st</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>a4c5fc89c5a092247981a060ba1b1d25c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int(*</type>
      <name>cb_func</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>aa921b1670b000b3ee8252d92a2769401</anchor>
      <arglist>)(link_node_st *, void *)</arglist>
    </member>
    <member kind="function">
      <type>link_list_st *</type>
      <name>link_list_init</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>a2aaabdf1ce440e05e148e1f9ff3b4084</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>link_list_free</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>a2a6c90057b3c053ee5cfdb796bf4b7c0</anchor>
      <arglist>(link_list_st *list)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_list_pop</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>aac5aa711b7242bc3f12bf6760adbbcb3</anchor>
      <arglist>(link_list_st *)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_list_top</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>ad71ea66d03b908c9f7298b75cd7799dc</anchor>
      <arglist>(link_list_st *)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_list_append</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>a4312dfaf969b900ce174f68d9fbc72a5</anchor>
      <arglist>(link_list_st *, link_node_st *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>link_list_traverse</name>
      <anchorfile>d4/d51/link__list_8h.html</anchorfile>
      <anchor>afd117605817c1af8030b9a73782ca77e</anchor>
      <arglist>(link_list_st *, cb_func callback, void *cb_data)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>link_node.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>dc/d77/link__node_8c</filename>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">error.h</includes>
    <includes id="d9/d56/link__node_8h" name="link_node.h" local="yes" imported="no">link_node.h</includes>
    <class kind="struct">link_node</class>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_node_new</name>
      <anchorfile>dc/d77/link__node_8c.html</anchorfile>
      <anchor>af7ba50773607e9774e4e20cb24b19527</anchor>
      <arglist>(void *data, free_cb free_func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>link_node_free</name>
      <anchorfile>dc/d77/link__node_8c.html</anchorfile>
      <anchor>a2606fcd601a9b77c13234bf847ad1b65</anchor>
      <arglist>(link_node_st *node)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>link_node_get_data</name>
      <anchorfile>dc/d77/link__node_8c.html</anchorfile>
      <anchor>a04fe6f17c83d9658510c00d19856433e</anchor>
      <arglist>(link_node_st *node)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_node_append</name>
      <anchorfile>dc/d77/link__node_8c.html</anchorfile>
      <anchor>a4dde9e385536119d6834c895728160bf</anchor>
      <arglist>(link_node_st *node_prev, link_node_st *node_next)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_node_get_next</name>
      <anchorfile>dc/d77/link__node_8c.html</anchorfile>
      <anchor>aedfe5d6c48f9d03ab7617e784a6729ea</anchor>
      <arglist>(link_node_st *node)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>link_node_remove_all</name>
      <anchorfile>dc/d77/link__node_8c.html</anchorfile>
      <anchor>a781932d213ea15e53cfeb1cea5d17b77</anchor>
      <arglist>(link_node_st **head)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>link_node.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>d9/d56/link__node_8h</filename>
    <member kind="typedef">
      <type>struct link_node</type>
      <name>link_node_st</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>a31d2b1397d1336a39843e6de139c01eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>free_cb</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>acfc68159fa6866b041419d97232c91c6</anchor>
      <arglist>)(void *)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_node_new</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>af7ba50773607e9774e4e20cb24b19527</anchor>
      <arglist>(void *data, free_cb free_func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>link_node_free</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>af441e89cf4d605d8dd7104ee0083e9b8</anchor>
      <arglist>(link_node_st *)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>link_node_get_data</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>ada753532a5f89458cc5d802d0e55b5ae</anchor>
      <arglist>(link_node_st *)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_node_append</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>a7e541af01c157643be1e8e9c65d58b83</anchor>
      <arglist>(link_node_st *, link_node_st *)</arglist>
    </member>
    <member kind="function">
      <type>link_node_st *</type>
      <name>link_node_get_next</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>a1dc14e7650fd9e3e84119727e3d55b00</anchor>
      <arglist>(link_node_st *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>link_node_remove_all</name>
      <anchorfile>d9/d56/link__node_8h.html</anchorfile>
      <anchor>a548a24025b3fd7f68475731ffdca3416</anchor>
      <arglist>(link_node_st **)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>parsing_tree.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>db/d47/parsing__tree_8c</filename>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">error.h</includes>
    <includes id="d4/da2/parsing__tree_8h" name="parsing_tree.h" local="yes" imported="no">parsing_tree.h</includes>
    <class kind="struct">parsing_tree</class>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_new</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>a98a826cd9c268ce4a9fbd55fd7c1a1c8</anchor>
      <arglist>(void *data, free_treenode_cb free_func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parsing_tree_free</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>af959530551fc78a4e21ad668f3d62e10</anchor>
      <arglist>(parsing_tree_st *tree_root)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_set_sibling</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>a94e5c8a43bc06f15bb63db3ed904540a</anchor>
      <arglist>(parsing_tree_st *tree_root, parsing_tree_st *sibling)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_set_child</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>a2bbb5123b05edfff7a6649cfe57aca06</anchor>
      <arglist>(parsing_tree_st *tree_root, parsing_tree_st *child)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_get_sibling</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>a7e5e4d6a9613dde756aa010a54ae4f6d</anchor>
      <arglist>(parsing_tree_st *tree_root)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_get_child</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>a2467b4faa5f4f5d73fa587819cbe162a</anchor>
      <arglist>(parsing_tree_st *tree_root)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>parsing_tree_get_data</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>a69b333ff7d72d472b5e6a65e8535f36d</anchor>
      <arglist>(parsing_tree_st *tree_root)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parsing_tree_prefix_traverse</name>
      <anchorfile>db/d47/parsing__tree_8c.html</anchorfile>
      <anchor>af1f3b3bd44a9caf714477e87fddff9f9</anchor>
      <arglist>(parsing_tree_st *tree_root, tree_traversal_cb cb_func, void *cb_data)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>parsing_tree.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>d4/da2/parsing__tree_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>TREE_TRAVERSE_CONTINUE</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>afb16975a0ba3194ff955a81481ed18b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TREE_TRAVERSE_STOP</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a3afd7455d3a599ed078d62a0c890e0c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct parsing_tree</type>
      <name>parsing_tree_st</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>ae8b094e7d34f1a9f220acc905780b752</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(*</type>
      <name>free_treenode_cb</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>aec1192e81ad70a250da35b5feecd4573</anchor>
      <arglist>)(void *)</arglist>
    </member>
    <member kind="typedef">
      <type>int(*</type>
      <name>tree_traversal_cb</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a366fe533172349c6b353cd0e18d40c62</anchor>
      <arglist>)(parsing_tree_st *, void *)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_new</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a98a826cd9c268ce4a9fbd55fd7c1a1c8</anchor>
      <arglist>(void *data, free_treenode_cb free_func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parsing_tree_free</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>ad10c5000739ed92533016b0e9b5d8993</anchor>
      <arglist>(parsing_tree_st *)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_set_sibling</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a79490c9cfb9aefc40ca0b2e5b6dd3d3b</anchor>
      <arglist>(parsing_tree_st *, parsing_tree_st *)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_set_child</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>aac69d492b26d17980ce886419f92906e</anchor>
      <arglist>(parsing_tree_st *, parsing_tree_st *)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_get_sibling</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a1dd00208f0cbf1edaeb3e2082005939a</anchor>
      <arglist>(parsing_tree_st *)</arglist>
    </member>
    <member kind="function">
      <type>parsing_tree_st *</type>
      <name>parsing_tree_get_child</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a88427e1c939a80422efaa187eb55c15d</anchor>
      <arglist>(parsing_tree_st *)</arglist>
    </member>
    <member kind="function">
      <type>void *</type>
      <name>parsing_tree_get_data</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a48f8befb3da13479bb8efb24fbfc492c</anchor>
      <arglist>(parsing_tree_st *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>parsing_tree_prefix_traverse</name>
      <anchorfile>d4/da2/parsing__tree_8h.html</anchorfile>
      <anchor>a93889760a5adeb3e66ac4380981328a0</anchor>
      <arglist>(parsing_tree_st *, tree_traversal_cb, void *)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>symbol_table.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>d0/d9d/symbol__table_8c</filename>
    <includes id="da/d41/error_8h" name="error.h" local="yes" imported="no">error.h</includes>
    <includes id="d2/dd5/symbol__table_8h" name="symbol_table.h" local="yes" imported="no">symbol_table.h</includes>
    <class kind="struct">symbol</class>
    <class kind="struct">symbol_table</class>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_ARRAY_SIZE</name>
      <anchorfile>d0/d9d/symbol__table_8c.html</anchorfile>
      <anchor>a72040e80321fca59f8af8edf32c9ad57</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ENLARGE_FACTOR</name>
      <anchorfile>d0/d9d/symbol__table_8c.html</anchorfile>
      <anchor>a59e33ec07bb1a561dc763265eee3c3a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct symbol</type>
      <name>symbol_st</name>
      <anchorfile>d0/d9d/symbol__table_8c.html</anchorfile>
      <anchor>a0600eeed1f7e59f81e37f6b2717b5655</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>symbol_table_st *</type>
      <name>symbol_table_init</name>
      <anchorfile>d0/d9d/symbol__table_8c.html</anchorfile>
      <anchor>a94fb5585ca4c9b1593a906dd3f345c65</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>symbol_table_fini</name>
      <anchorfile>d0/d9d/symbol__table_8c.html</anchorfile>
      <anchor>adf1040197e53d678030071549eaa479e</anchor>
      <arglist>(symbol_table_st *symbol_table)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>symbol_table_lookup</name>
      <anchorfile>d0/d9d/symbol__table_8c.html</anchorfile>
      <anchor>a21d921c650af20fb7f9b1eb9bb5ae03d</anchor>
      <arglist>(symbol_table_st *symbol_table, char *symbol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>symbol_table_insert</name>
      <anchorfile>d0/d9d/symbol__table_8c.html</anchorfile>
      <anchor>a76c998ad6ef1df3298afb862885be54f</anchor>
      <arglist>(symbol_table_st *symbol_table, char *symbol, int token_type)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>symbol_table.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/compiler/utils/</path>
    <filename>d2/dd5/symbol__table_8h</filename>
    <member kind="typedef">
      <type>struct symbol_table</type>
      <name>symbol_table_st</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>adb720cc5a71cd08785a1a1d4d4beabb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>type</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NONE</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2dac157bdf0b85a40d2619cbc8bc1ae5fe2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>KEYWORD</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da129281444e94f5f509cba213d51a814d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDENTIFIER</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da84f8ae2490f9e4bd2321fd21f4b0e807</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BIN_OP</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da6368a1f161bfa27c5d8c82b8d21254a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NUMBER</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da12a90dfe20486bbe3e075afcd19ef2d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DELIMITER</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2daac89a86c2ea494ef8a09054e99fab96e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BOOLEAN_OP</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da32ea4cf3e4933d06248caea66308f31c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ID</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da001479a58fb44c39a29b20d565081a68</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OPEN_PARENTHESES</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da531a8e2e638494bf9a4d4c70bb148afe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLOSE_PARENTHESES</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da1a0f1858f1514e5076d8bce1052ced22</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OPEN_CURLY_BRACKETS</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da64a8300c1c4675a394bc9d3b6a8d4d51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>CLOSE_CURLY_BRACKETS</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a7aead736a07eaf25623ad7bfa1f0ee2da3bb0a07da34af1d4013db04bdb7e90b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>symbol_table_st *</type>
      <name>symbol_table_init</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a94fb5585ca4c9b1593a906dd3f345c65</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>symbol_table_fini</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>a805533979c6489693ddcd654e8f083e9</anchor>
      <arglist>(symbol_table_st *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>symbol_table_lookup</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>acb348ac5e72ee0799fcf4d32d50a47e9</anchor>
      <arglist>(symbol_table_st *, char *symbol)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>symbol_table_insert</name>
      <anchorfile>d2/dd5/symbol__table_8h.html</anchorfile>
      <anchor>aa8fa38dcf63c88c3ec2e9b80de29c83d</anchor>
      <arglist>(symbol_table_st *, char *symbol, int token_type)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>instruction.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/runtime/</path>
    <filename>d3/dce/instruction_8c</filename>
    <includes id="d8/df4/instruction_8h" name="instruction.h" local="yes" imported="no">instruction.h</includes>
    <class kind="struct">label_info</class>
    <class kind="struct">label_table</class>
    <class kind="struct">instruction</class>
    <class kind="struct">instruction_set</class>
    <member kind="define">
      <type>#define</type>
      <name>BUFFER_SIZE</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a6b20d41d6252e9871430c242cb1a56e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DEFAULT_ARRAY_SIZE</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a72040e80321fca59f8af8edf32c9ad57</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RESIZE_FACTOR</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>ab4207f3a0ad0e23bc354d2a8f1f5ddc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct label_info</type>
      <name>label_st</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a7afff4c039736bfaad4328d0ebe59325</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct label_table</type>
      <name>label_table_st</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a3ed5edb64f6d1fe60e3a0426e3ce71bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>s_load_program</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a584a850d902eaa3b99cf0d8d0f1578d6</anchor>
      <arglist>(const char *, instruction_set_st *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>s_replace_label</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a90593b633e5736b1635c089a06e0aad2</anchor>
      <arglist>(instruction_set_st *, label_table_st *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>s_insert_label</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>adfa551da2a6d6d2086f3fffb509369d2</anchor>
      <arglist>(label_table_st *, char *, unsigned int)</arglist>
    </member>
    <member kind="function">
      <type>instruction_set_st *</type>
      <name>instruction_load_program</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>ae9f2e9463daa2609b631c183582ae7c2</anchor>
      <arglist>(const char *file_path)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>instruction_clean_up</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>aaa4452fed08cc20654997da4290c4b44</anchor>
      <arglist>(instruction_set_st *instructions)</arglist>
    </member>
    <member kind="function">
      <type>instruction_st *</type>
      <name>instruction_set_get_instruction</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a7d928df98010b168d2701cf5d9244895</anchor>
      <arglist>(instruction_set_st *instructions)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>instruction_set_set_pc</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a7333984b616e77b7058e16d149244ddf</anchor>
      <arglist>(instruction_set_st *instructions, int new_pc)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>instruction_set_get_flag</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a1d51c7ddb6cd9fe30951985fda2687ed</anchor>
      <arglist>(instruction_set_st *instructions)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>instruction_set_set_flag</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a7016eee19add198d8de2c8a70a9a880e</anchor>
      <arglist>(instruction_set_st *instructions, int new_flag)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>instruction_set_get_label</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>af0742d4d91320013ada93ab063ebbef7</anchor>
      <arglist>(instruction_set_st *instructions, char *label)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>instruction_get_op_code</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>ae21eeb913d0837ed7ef943a87686f4fc</anchor>
      <arglist>(instruction_st *instruction)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>instruction_get_op_first</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>a799c31f66403ff557da1e759311529ae</anchor>
      <arglist>(instruction_st *instruction)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>instruction_get_op_second</name>
      <anchorfile>d3/dce/instruction_8c.html</anchorfile>
      <anchor>ac57c978878707d2740bc9d0b8173b02f</anchor>
      <arglist>(instruction_st *instruction)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>instruction.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/runtime/</path>
    <filename>d8/df4/instruction_8h</filename>
    <member kind="typedef">
      <type>struct instruction</type>
      <name>instruction_st</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>af751a7ed8d973c2b23a50982f7627664</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct instruction_set</type>
      <name>instruction_set_st</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a4363a52592266b681dec63cb4c84eb7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>instruction_set_st *</type>
      <name>instruction_load_program</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a1c6e676979fa0e8127f7e699eecfffcd</anchor>
      <arglist>(const char *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>instruction_clean_up</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>ab7094a97fb9057085d45c53a559b7878</anchor>
      <arglist>(instruction_set_st *)</arglist>
    </member>
    <member kind="function">
      <type>instruction_st *</type>
      <name>instruction_set_get_instruction</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a3d5ab8551a894157210f51b7f5bc6bb1</anchor>
      <arglist>(instruction_set_st *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>instruction_set_set_pc</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a26542b9ff1fdf30cfdb874f1f5ae5c2c</anchor>
      <arglist>(instruction_set_st *, int)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>instruction_set_get_flag</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a7a755cdf647b50fcc640ba6266397b76</anchor>
      <arglist>(instruction_set_st *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>instruction_set_set_flag</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>ae0c051a27f560d8fb4c813279d50fd77</anchor>
      <arglist>(instruction_set_st *, int)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>instruction_set_get_label</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>ae78a4642024fb06e1e590dab603b9dce</anchor>
      <arglist>(instruction_set_st *, char *)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>instruction_get_op_code</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a9e218f3d9dfaa783e76342f9c36c248a</anchor>
      <arglist>(instruction_st *)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>instruction_get_op_first</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a20bda851ba4f9bf0a98d914d16585c50</anchor>
      <arglist>(instruction_st *)</arglist>
    </member>
    <member kind="function">
      <type>char *</type>
      <name>instruction_get_op_second</name>
      <anchorfile>d8/df4/instruction_8h.html</anchorfile>
      <anchor>a4835a773f1c137ba44a13bfbb6d01642</anchor>
      <arglist>(instruction_st *)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>runtime.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/runtime/</path>
    <filename>de/d2b/runtime_8c</filename>
    <includes id="d8/d6b/storage_8h" name="storage.h" local="yes" imported="no">storage.h</includes>
    <includes id="d8/df4/instruction_8h" name="instruction.h" local="yes" imported="no">instruction.h</includes>
    <class kind="struct">operation</class>
    <member kind="typedef">
      <type>void(*</type>
      <name>eval</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a834389cb528e7aa941ca364fd20b4494</anchor>
      <arglist>)(void *, void *)</arglist>
    </member>
    <member kind="typedef">
      <type>int(*</type>
      <name>cmp_cb</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>abdf8e3d51b81ff73996052750acaa76b</anchor>
      <arglist>)(int)</arglist>
    </member>
    <member kind="typedef">
      <type>struct operation</type>
      <name>operation_st</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>ae03ddee3906158cdc578f151a2263efc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_bin_op_helper</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a739a8de3aa0fba3496fd90f1f239e8be</anchor>
      <arglist>(void *, void *, char)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_dec</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a10b90ea32b74d3ba558950ecde02046c</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_mov</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>ac87aa4fb126a56d7f6b61f67813b5cf2</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_out</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a73cc93a82b1e0b74e472b0cd2897ef64</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_add</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a758f02ee66779f8b3e72b8526897ec21</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_sub</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a9826472035d992496091a6fb6709effb</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_mul</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a0108a717dbdbf1491ca0e5d913e1768b</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_div</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a2e2d5655a43de21f16a35591500752c8</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_mod</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a40e43a982e36e2f4220abfa26ed3aaaa</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_cmp</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a262d23032d3b840b37ace9693d8282a6</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_je</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>aacbb65dcf27c689c812fb94cb4681280</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_jne</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a426c0ba3bfb0cded2c763143c5a459f4</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_jl</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>af9bf249baf8657e8e6491da00703aaea</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_jle</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>aabea51e672196097a9fd0bf65459c5f7</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_jg</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a25df3e93df5877163aba77ab2c0e7127</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_jge</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a8be4f11402363c4b4c5ea4c1dcdc709e</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_jmp</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>aace6ec220016e8f4bef73886a98c95eb</anchor>
      <arglist>(void *, void *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>eval_bool_op_helper</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a8707c106c83af158a9675df46298301f</anchor>
      <arglist>(void *, void *, cmp_cb flag_cmp)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>cmp_je</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a9f9e34c537ace520cab2e50d35616df5</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>cmp_jne</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>ae0b347cbc90b9249b32364cbecae352d</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>cmp_jl</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>aa5453d5fa223609627d2371f619542cb</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>cmp_jle</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>ab825676a78225ac5c47c21e427e12a2c</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>cmp_jg</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a578f004f0458d704dcda34703b063e26</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>cmp_jge</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a283e10e6d3458881a18c4222b1ae24f7</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>cmp_jmp</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a3feeb11f2864c7066e60e33e85803a8f</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>s_evaluate</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>aaa59eb26f84b0218fdb7d5c582604a13</anchor>
      <arglist>(instruction_set_st *)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>s_usage</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>af52a5d5ea91424c6e657b417d4ffd515</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>a0ddf1224851353fc92bfbff6f499fa97</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static machine_memory_st *</type>
      <name>s_machine_store</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>afd2e316e584e88d641f5ab7c4021eaa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static instruction_set_st *</type>
      <name>s_instructions</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>abf395669daa34407f9a4203dd738284b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static operation_st</type>
      <name>g_operations</name>
      <anchorfile>de/d2b/runtime_8c.html</anchorfile>
      <anchor>aea0c52a821201bf5cfd9e0aa455422c4</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storage.c</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/runtime/</path>
    <filename>d2/dd2/storage_8c</filename>
    <includes id="d8/d6b/storage_8h" name="storage.h" local="yes" imported="no">storage.h</includes>
    <class kind="struct">memory</class>
    <class kind="struct">machine_memory</class>
    <member kind="define">
      <type>#define</type>
      <name>STATIC_MEMORY_SIZE</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>a1f31d6774c98cae44b278fa39be6c6d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SCOPE_BOUNDRAY_SIZE</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>aaf97a7c5cbe60ecb1532d9e799ed44e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>RESIZE_FACTOR</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>ab4207f3a0ad0e23bc354d2a8f1f5ddc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>machine_memory_st *</type>
      <name>machine_memory_init</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>ac8add65f6ee5035c0b569faabcfde226</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>machine_memory_fini</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>a150edbc070f5ff72118b964a41b832b7</anchor>
      <arglist>(machine_memory_st *machine_store)</arglist>
    </member>
    <member kind="function">
      <type>memory_st *</type>
      <name>machine_memory_get_variable</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>a5fd47e8ceac6a2a4415ff92313413a29</anchor>
      <arglist>(machine_memory_st *machine_store, char *variable_name, int scope)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>machine_memory_set_variable</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>aaa9dc820debbe71e33fd3f4bf7aad29b</anchor>
      <arglist>(machine_memory_st *machine_store, char *variable_name, int value, int scope)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>machine_memory_open_scope</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>a33b95b8d978963de0f29653b30b320a5</anchor>
      <arglist>(machine_memory_st *machine_store)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>machine_memory_close_scope</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>a4112369e514ce461ee20b409c4aec0a8</anchor>
      <arglist>(machine_memory_st *machine_store)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>memory_get_value</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>a7cc5ea76fac4bebd62b61bacee377cf0</anchor>
      <arglist>(memory_st *variable)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>memory_set_value</name>
      <anchorfile>d2/dd2/storage_8c.html</anchorfile>
      <anchor>a2372d87c5e2d562b76da9d9d9942c745</anchor>
      <arglist>(memory_st *variable, int value)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>storage.h</name>
    <path>/Users/tobielf/Documents/GitHub/ASU-SER502/src/runtime/</path>
    <filename>d8/d6b/storage_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>MEMORY_CURRENT_SCOPE</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>aab21b20c6408c1ed1bb80e59a4444f8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MEMORY_ALL_SCOPE</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>aeea245bc9884ecdea2ab0c1d33ba0e64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct memory</type>
      <name>memory_st</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>aed8028d0ec206674c6ccbf2549e6c2bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct machine_memory</type>
      <name>machine_memory_st</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>a7a2fcbc3faf6d78305c3c96b7ac50663</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>machine_memory_st *</type>
      <name>machine_memory_init</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>ac8add65f6ee5035c0b569faabcfde226</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>machine_memory_fini</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>a023971632fd73a4e5b92051b9619e625</anchor>
      <arglist>(machine_memory_st *)</arglist>
    </member>
    <member kind="function">
      <type>memory_st *</type>
      <name>machine_memory_get_variable</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>a1a804cb9568c862821d216998016efa3</anchor>
      <arglist>(machine_memory_st *, char *, int)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>machine_memory_set_variable</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>aea68f656effa784fec1deaa7fef72868</anchor>
      <arglist>(machine_memory_st *, char *, int, int)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>machine_memory_open_scope</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>ad385230b89c9a7df85849db172d5e64b</anchor>
      <arglist>(machine_memory_st *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>machine_memory_close_scope</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>a065087455b3d36a381e9db63a7c82d95</anchor>
      <arglist>(machine_memory_st *)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>memory_get_value</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>a30520ba7edab783c77b11002c3f431d2</anchor>
      <arglist>(memory_st *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>memory_set_value</name>
      <anchorfile>d8/d6b/storage_8h.html</anchorfile>
      <anchor>a27afe58a0e0802f69ccdaef0aa93e231</anchor>
      <arglist>(memory_st *, int)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>instruction</name>
    <filename>de/ddf/structinstruction.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>op_code</name>
      <anchorfile>de/ddf/structinstruction.html</anchorfile>
      <anchor>ac32a103e42c81c5932d241748f5900b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>op_first</name>
      <anchorfile>de/ddf/structinstruction.html</anchorfile>
      <anchor>a312f9ff274ea41f46200188297c7e394</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>char *</type>
      <name>op_second</name>
      <anchorfile>de/ddf/structinstruction.html</anchorfile>
      <anchor>a904c6d76f2e7db7239139b56997873da</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>instruction_set</name>
    <filename>d4/d04/structinstruction__set.html</filename>
    <member kind="variable">
      <type>instruction_st *</type>
      <name>instructs</name>
      <anchorfile>d4/d04/structinstruction__set.html</anchorfile>
      <anchor>a7349d4f79ebee41a093e125ee7e552db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>label_table_st *</type>
      <name>labels</name>
      <anchorfile>d4/d04/structinstruction__set.html</anchorfile>
      <anchor>a98fcf17fc2e258c26b42cb78e0f4920c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>count</name>
      <anchorfile>d4/d04/structinstruction__set.html</anchorfile>
      <anchor>ab6f8f13bde72ef7bc244922a78126422</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>program_counter</name>
      <anchorfile>d4/d04/structinstruction__set.html</anchorfile>
      <anchor>a18585a3e11caf571ac6fd2037edaafbb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>flag_register</name>
      <anchorfile>d4/d04/structinstruction__set.html</anchorfile>
      <anchor>a8a44ddf283d78ab6d5e1241d4a2bc296</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>label_info</name>
    <filename>d7/de1/structlabel__info.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>label_name</name>
      <anchorfile>d7/de1/structlabel__info.html</anchorfile>
      <anchor>a2804709052b4e0f81855c3326d186053</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>address</name>
      <anchorfile>d7/de1/structlabel__info.html</anchorfile>
      <anchor>a1fc0cd69d9ee2b00f221b1594c0800fd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>label_table</name>
    <filename>d7/d18/structlabel__table.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>label_table_capacity</name>
      <anchorfile>d7/d18/structlabel__table.html</anchorfile>
      <anchor>aad170a4c708408896e0085bd469c6790</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>label_table_size</name>
      <anchorfile>d7/d18/structlabel__table.html</anchorfile>
      <anchor>ac5a6cbfae3efdf0ab65dbe1e8308440e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>label_st *</type>
      <name>label_table</name>
      <anchorfile>d7/d18/structlabel__table.html</anchorfile>
      <anchor>aea04b9d7a451403ddd304fa1d6cd4bab</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>link_list</name>
    <filename>d8/dba/structlink__list.html</filename>
    <member kind="variable">
      <type>link_node_st *</type>
      <name>head</name>
      <anchorfile>d8/dba/structlink__list.html</anchorfile>
      <anchor>a7d9e948f665c5272d0de852d38620ffc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>link_node_st *</type>
      <name>tail</name>
      <anchorfile>d8/dba/structlink__list.html</anchorfile>
      <anchor>a57cf0987d22ecb180af7a03444608e95</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>link_node</name>
    <filename>dc/dd6/structlink__node.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>data</name>
      <anchorfile>dc/dd6/structlink__node.html</anchorfile>
      <anchor>acb13d847a9a7603c6b5f0d74afb3bda7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>free_cb</type>
      <name>free_func</name>
      <anchorfile>dc/dd6/structlink__node.html</anchorfile>
      <anchor>a8d9b42f9934a879c907a33674db12c71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>link_node_st *</type>
      <name>next</name>
      <anchorfile>dc/dd6/structlink__node.html</anchorfile>
      <anchor>a5df1da2737ab14c933a7f926f09e8a4e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>machine_memory</name>
    <filename>d8/dbc/structmachine__memory.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>allocated_address</name>
      <anchorfile>d8/dbc/structmachine__memory.html</anchorfile>
      <anchor>a7db8e9762af052da5a890f756b83aa7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>memory_size</name>
      <anchorfile>d8/dbc/structmachine__memory.html</anchorfile>
      <anchor>a930dffcdfdcfebfa96689c74f6cd1084</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>current_scope</name>
      <anchorfile>d8/dbc/structmachine__memory.html</anchorfile>
      <anchor>a7f1c623bd55ce4ec91a891ee80f9ee80</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int *</type>
      <name>scope_boundary</name>
      <anchorfile>d8/dbc/structmachine__memory.html</anchorfile>
      <anchor>a619ae94a94f8ca3a4a4e15ac443f5e00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>scope_capacity</name>
      <anchorfile>d8/dbc/structmachine__memory.html</anchorfile>
      <anchor>a901f324146f590bfe19d2aafad21353e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>memory_st *</type>
      <name>static_memory</name>
      <anchorfile>d8/dbc/structmachine__memory.html</anchorfile>
      <anchor>a7eb673bc62b7ebbb95e9e3c3a29557ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>memory</name>
    <filename>dd/db0/structmemory.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>variable_name</name>
      <anchorfile>dd/db0/structmemory.html</anchorfile>
      <anchor>aed61d877bb3efd678d19420e051b99c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>variable_value</name>
      <anchorfile>dd/db0/structmemory.html</anchorfile>
      <anchor>ac05406f5d65c3671e933912d2a3b569e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>scope</name>
      <anchorfile>dd/db0/structmemory.html</anchorfile>
      <anchor>abd4c71111c25e444a3b315e83ae40ee1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>operation</name>
    <filename>d9/dc0/structoperation.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>op_code</name>
      <anchorfile>d9/dc0/structoperation.html</anchorfile>
      <anchor>ac3940b443b4b030da1c9157fe35aa103</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>eval</type>
      <name>eval_func</name>
      <anchorfile>d9/dc0/structoperation.html</anchorfile>
      <anchor>ab6a6f54a6c98a7b85a82c6cb77c4926d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>parsing_tree</name>
    <filename>d8/d02/structparsing__tree.html</filename>
    <member kind="variable">
      <type>void *</type>
      <name>data</name>
      <anchorfile>d8/d02/structparsing__tree.html</anchorfile>
      <anchor>ae207f8a2c9a95e9c9259e64e33433c7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>free_treenode_cb</type>
      <name>free_func</name>
      <anchorfile>d8/d02/structparsing__tree.html</anchorfile>
      <anchor>a82369455c5ebe46a53af3ffa8c9f87f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parsing_tree_st *</type>
      <name>child</name>
      <anchorfile>d8/d02/structparsing__tree.html</anchorfile>
      <anchor>ae8bbce56420d3b41f66561f63d395378</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>parsing_tree_st *</type>
      <name>sibling</name>
      <anchorfile>d8/d02/structparsing__tree.html</anchorfile>
      <anchor>a0077c3f7de81c82d93150a6440cd222c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>symbol</name>
    <filename>d1/d8d/structsymbol.html</filename>
    <member kind="variable">
      <type>char *</type>
      <name>symbol</name>
      <anchorfile>d1/d8d/structsymbol.html</anchorfile>
      <anchor>a2035d0d47ff16a7572380ee804c53369</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>token_type</name>
      <anchorfile>d1/d8d/structsymbol.html</anchorfile>
      <anchor>ab391333c670a953bffc1c0ed8612d153</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>symbol_table</name>
    <filename>d0/d19/structsymbol__table.html</filename>
    <member kind="variable">
      <type>symbol_st *</type>
      <name>symbol_array</name>
      <anchorfile>d0/d19/structsymbol__table.html</anchorfile>
      <anchor>aa88c63669b435652e632b27369b004a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>array_size</name>
      <anchorfile>d0/d19/structsymbol__table.html</anchorfile>
      <anchor>a383580eb2137fb0eea4956684a3c829b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>table_size</name>
      <anchorfile>d0/d19/structsymbol__table.html</anchorfile>
      <anchor>aba6818932b0bdf0bca2e8a7ba1dd2ff7</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
