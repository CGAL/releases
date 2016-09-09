#!/usr/local/bin/perl -w
#
# Copyright (c) 1998,1999,2000,2001,2002  Utrecht University (The Netherlands),
# ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
# INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
# (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
# and Tel-Aviv University (Israel).  All rights reserved.
#
# This file is part of CGAL (www.cgal.org); you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; version 2.1 of the License.
# See the file LICENSE.LGPL distributed with CGAL.
#
# Licensees holding a valid commercial license may use this file in
# accordance with the commercial license agreement provided with the software.
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/scripts/filtered_predicates_generator.pl,v $
# $Revision: 1.26 $ $Date: 2003/10/22 08:24:26 $
# $Name: current_submission $
#
# Author(s)     : Sylvain Pion


# This script takes as input a source code file containing template predicates.
# It outputs the filtered specializations.
#
# See the CGAL documentation: Support Library, Number Types.

# TODO:
# - Split the lines only if the result is larger than 80 characters ?
#   ( or use a C++ code indenter ? )
# - Separate the classes in other files ?  (they are needed by libCGAL)
# - While parsing, remove CGAL_assertion() and co from the original code.
# - Add assertions about the epsilons being updated.

use vars qw($opt_p $opt_h $opt_d $opt_v $opt_l $opt_s); # Suppress warnings
require 'getopt.pl';

# Global variables
%known_ret_types=("bool", 1);	# Known allowed return types (see main())
@predicates=(			# list of predicates, with the built-ins.
# CGAL::, template_type, inline, ret_type, fct_name, #eps, body, new_body, args
    [ "", "NT", "inline", "Comparison_result", "compare", 1, "", "", "a", "b"],
    [ "", "NT", "inline", "Sign", "sign", 1, "", "", "x"] );
# Note: we don't actually care about a few fields ($body...) for these.
$num_built_in_predicates=$#predicates+1;     # Number of built-in predicates.
$pred_list_re="sign|compare";

# We _must_ manipulate the fields of @predicate using these constants:
# (aren't there structs in Perl ?  Are packs the way to go ? )
# ($CGAL_pos, $template_type_pos, $inline_pos, $ret_type_pos)=(0..3); # unused
($fct_name_pos, $eps_pos, $body_pos, $new_body_pos, $args_pos)=(4..8);

# Useful regexps.
$C_symbol_re='[a-zA-Z_]\w*';			# A pure C symbol name.
$CGAL_symbol_re='(?:CGAL::|)'.$C_symbol_re;	# Idem with eventually 'CGAL::'

# Parse the command line options.
sub parse_command_line {
  Getopt('iodl');
  if ($opt_h) {
    warn "Usage: filtered_predicate_converter [options]
    -i file   : specify the main input source file [default is stdin]
    -o file   : specify the main output file       [default is stdout]
    -s        : also want the static adaptative filters [default is off]
    -l file   : indicate the output file that will receive the static part.
    -d files  : list of dependant predicates file (concatenated with \":\")
                by default, only the built-in predicates are known.
                (typically, it's just sign_of_determinant.h that you want)
		(it's only useful when \"-s\" is here too).
    -p        : be pedantic (change warnings to errors)
    -h        : print this help\n";
    exit;
  }
  @dependancy_files = split(':', $opt_d) if ($opt_d);
  $opt_i = "-" unless $opt_i;
  $opt_o = "-" unless $opt_o;
  if (not $opt_l) {
    warning("The -l option is compulsory for the static filters.");
  }
  $pedantic = $opt_p;
  $want_statics = $opt_s;
}

# Auxiliary routine to emit a warning and die if pedantic.
sub warning {
  warn "// Warning : @_\n";
  die if $pedantic;
}

# Parse the CGAL header
sub parse_CGAL_header {
  local ($_) = @_;
  my $file_name = $1 if m#//\.*Source: \.*/include/CGAL/(.*)#m;
  my $rest      = $' if /^#ifndef[\s]*([\S]*_H)\s*?/m;
  $_ = $1;
  $_ = "CGAL_$_" unless /CGAL_/;
  s/CGAL_/CGAL_ARITHMETIC_FILTER_/;
  return ($_, $file_name, $rest);
}

# Print the new CGAL header
sub print_CGAL_header {
  my ($output_file, $new_protect_name, $file_name) = @_;
  print $output_file
"// Copyright (c) 1997-2003  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// \$"."Source: \$
// \$"."Revision: \$ \$"."Date: \$
// \$"."Name:  \$
//
// Author(s)     : Sylvain Pion

// This file is automatically generated by
// scripts/filtered_predicates_generator.pl

#ifndef $new_protect_name
#define $new_protect_name

#include <CGAL/Profile_counter.h>

CGAL_BEGIN_NAMESPACE
template <class ET> class Lazy_exact_nt;
CGAL_END_NAMESPACE\n\n";
}

# Print dynamic versions
sub print_dynamic {
  my ($CGAL, $t, $inline, $ret_type, $fct_name, $e, $b, $n, @args)=@_;
  my $type = "const ${CGAL}Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, ${CGAL}Dynamic,"
             ." CGAL_IA_PROTECTED, CGAL_IA_CACHE>";
  my $type2 = "const ${CGAL}Lazy_exact_nt<ET>";
  my $args_call  = join ",", map "\n    $type &$_", @args;
  my $args_call2 = join ",", map "\n    $type2 &$_", @args;
  my $args_inter = join ",", map "\n\t\t$_.interval()", @args;
  my $args_exact = join ",", map "\n\t\t$_.exact()", @args;

  print FO
"#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, bool CGAL_IA_PROTECTED,
           class CGAL_IA_CACHE >
#else
static
#endif
/* $inline */
$ret_type
$fct_name($args_call)
{
  try
  {
    CGAL_PROFILER(\"IA $fct_name calls\");
    ${CGAL}Protect_FPU_rounding<CGAL_IA_PROTECTED> Protection;
    return $fct_name($args_inter);
  } 
  catch (${CGAL}Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER(\"IA $fct_name failures\");
    ${CGAL}Protect_FPU_rounding<!CGAL_IA_PROTECTED> Protection(CGAL_FE_TONEAREST);
    return $fct_name($args_exact);
  }
}

#ifndef CGAL_CFG_MATCHING_BUG_2
template < class ET >
/* $inline */
$ret_type
$fct_name($args_call2)
{
  try
  {
    CGAL_PROFILER(\"Lazy IA $fct_name calls\");
    ${CGAL}Protect_FPU_rounding<true> Protection;
    return $fct_name($args_inter);
  } 
  catch (${CGAL}Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER(\"Lazy IA $fct_name failures\");
    ${CGAL}Protect_FPU_rounding<false> Protection(CGAL_FE_TONEAREST);
    return $fct_name($args_exact);
  }
}
#endif\n\n";
}

# Print static infos
sub print_static_infos {
  my ($CGAL, $t, $inline, $ret_type, $fct_name, $eps, $b, $new_body, @args)=@_;
  my $predicate_class_name = "Static_Filtered_$fct_name\_".($#args+1);

  print FL map("double $predicate_class_name\::_epsilon_$_;\n", 0..$eps-1);
  print FL "double $predicate_class_name\::_bound = -1.0;\n\n";
}

# Print the epsilon variant of the function
sub epsilon_function {
  my ($ret_type, $fct_name, $body, $t, $eps, $new_t, $const, @args) = @_;
  my $args_call = join ",", map "\n\tconst $new_t &$_", @args;
  my $eps_call  = join ",", map "\n\t${const}double & epsilon_$_", 0..$eps-1;
  # We just typedef the original template type at the beginning of the body.
  $_ = $body;
  s/{/{\n  typedef $new_t $t;\n/s;
  s/\n/\n  /msg;  # Indent
  s/update_epsilon/$fct_name/msg;
  return "static $ret_type $fct_name($args_call,$eps_call)$_";
}

# Print the struct corresponding to the predicate
sub print_predicate_struct {
  my ($CGAL, $t, $inline, $ret_type, $fct_name, $eps, $b, $new_body, @args)=@_;
  my $predicate_class_name = "Static_Filtered_$fct_name\_".($#args+1);
  my $epsilon_list = join ",", map "_epsilon_$_", 0..$eps-1;
  my $bound_list = "b," x ($#args+1);
  my $update_epsilon = epsilon_function($ret_type, "update_epsilon",
  		$new_body, $t, $eps, "${CGAL}Static_filter_error", "", @args);

  my $epsilon_variant = epsilon_function($ret_type, "epsilon_variant",
  		$new_body, $t, $eps, "Restricted_double", "const ", @args);
  print FO
"struct $predicate_class_name
{
  static double _bound;
  static double $epsilon_list;

  $update_epsilon

  // Call this function from the outside to update the context.
  static void new_bound (const double b) // , const double error = 0)
  {
    _bound = b;
    // recompute the epsilons: \"just\" call it over Static_filter_error.
    // That's the tricky part that might not work for everything.
    (void) update_epsilon($bound_list$epsilon_list);
    // TODO: We should verify that all epsilons have really been updated.
  }

  $epsilon_variant
};\n\n";
}

# Print static versions
sub print_static {
  my ($adv, $CGAL, $t, $inline, $ret_type, $fct_name, $eps, $b, $new_body,
      @args)=@_;

  my $predicate_class_name = "Static_Filtered_$fct_name\_".($#args+1);
  my $type = "const ${CGAL}Filtered_exact <CGAL_IA_CT, CGAL_IA_ET, ${CGAL}Static,"
            ." $adv, CGAL_IA_CACHE>";
  my $args_call     = join ",", map "\n    $type &$_", @args;
  my $args_dbl      = join ",", map "\n\t\t$_.dbl()", @args;
  my $args_exact    = join ",", map "\n\t\t$_.exact()", @args;
  my $args_epsilons = join ",",
     map "\n\t\t$predicate_class_name\::_epsilon_$_", 0..$eps-1;
  my $args_error    = "\n\t\tStatic_filter_error(SAF_bound)," x ($#args+1);
  my $bounds_check  = join " ||",
     map "\n\tfabs($_.to_double()) > SAF_bound", @args;
  my $compute_new_bound = join "",
     map "\n    NEW_bound = max(NEW_bound, fabs($_.to_double()));", @args;

  print FO
"#ifndef CGAL_CFG_MATCHING_BUG_2
template < class CGAL_IA_CT, class CGAL_IA_ET, class CGAL_IA_CACHE >
#else
static
#endif
/* $inline */
$ret_type
$fct_name($args_call)
{";

  if ($adv eq "false") {
    print FO "
  CGAL_assertion_code(
    const double SAF_bound = $predicate_class_name\::_bound; )
  CGAL_assertion(!($bounds_check));

  try
  {
    CGAL_PROFILER(\"ST $fct_name calls\");
    return $predicate_class_name\::epsilon_variant($args_dbl,$args_epsilons);
  }
  catch (...)
  {
    CGAL_PROFILER(\"ST $fct_name failures\");
    return $fct_name($args_exact);
  }";
  } else {
    print FO "
//   bool re_adjusted = false;
  const double SAF_bound = $predicate_class_name\::_bound;

  // Check the bounds.  All arguments must be <= SAF_bound.
  if ($bounds_check)
  {
// re_adjust:
    // Compute the new bound.
    double NEW_bound = 0.0;$compute_new_bound
    // Re-adjust the context.
    CGAL_PROFILER(\"SA $fct_name updates\");
    $predicate_class_name\::new_bound(NEW_bound);
  }

  try
  {
    CGAL_PROFILER(\"SA $fct_name calls\");
    return $predicate_class_name\::epsilon_variant($args_dbl,$args_epsilons);
  }
  catch (...)
  {
    // if (!re_adjusted) {  // It failed, we re-adjust once.
      // re_adjusted = true;
      // goto re_adjust;
    // }
    CGAL_PROFILER(\"SA $fct_name failures\");
    return $fct_name($args_exact);
  }";
  }
  print FO "\n}\n\n";
}

# Parse from "template" to end of body
sub parse_function_definition {
  local ($_) = @_;
  /^\W*template\s*\<\s*(?:class|typename)\s*(\S*)\s*\>	# template type name
    \W*(CGAL_\w*INLINE|inline|)			# eventual inline directive
    \W*($CGAL_symbol_re)			# return type
    \W*($C_symbol_re)				# function name
    .*?\((.*?)\)/smx;				# argument list
  my ($x, $body, $after) = extract_balanced("{", "}", $');
  my @pred = ($1, $2, $3, $4, -1, $body."}", "");
  my $fct_name = $4;
  if (not $known_ret_types{$3}) {
    warning("Return type \"$3\" of function \"$4\" is unknown");
  }
  foreach (split (',', $5)) {
    if (not /const/) {
      warning("Non const argument \"$_\" in function \"$fct_name\".");
    }
    /($C_symbol_re)\s*$/;
    push @pred, $1;
  }
  return ($after, @pred);
}

# Main parsing subroutine
sub parse_input_code {
  local ($_) = @_;
  my $CGAL = "CGAL::";
  # Treat NO_FILTER parts
  s#//CGAL_NO_FILTER_BEGIN.*?//CGAL_NO_FILTER_END##msg;
  s#/\*CGAL_NO_FILTER\*/#CGAL_NO_FILTER_MARK#sg; # De-comment no filter marks.
  # Note that the following are buggy if they appear in strings (cf Perl FAQ).
  s#//.*##mg;      # Remove C++ "//" comments
  s#/\*.*?\*/##sg; # Remove C "/**/" comments
  while (/(CGAL_(?:BEGIN|END)_NAMESPACE|template\s*\<.*?\>)/sm) {
    if ($1 eq "CGAL_BEGIN_NAMESPACE") { $CGAL=""; $_=$'; }
    elsif ($1 eq "CGAL_END_NAMESPACE") { $CGAL="CGAL::"; $_=$'; }
    else {
      my $rest = $1.$';
      $_=$';
      if ( ! /^[^\(]*?CGAL_NO_FILTER_MARK/s ) {
        my ($after, @pred) = parse_function_definition($rest);
        push @predicates, [ $CGAL, @pred ];
        $pred_list_re.="|".$pred[$fct_name_pos-1];
        treat_predicate($#predicates);
        $_ = $after;
      }
      else { $_=$'; }
    }
  }
}

# Print the code of the overloaded predicates
sub print_predicates {
  my $was_in_CGAL = 0;
  # We skip the built-in predicates.
  for $i ( $num_built_in_predicates .. $#predicates ) {
    my ($CGAL) = @{$predicates[$i]};
    print FO "CGAL_BEGIN_NAMESPACE\n\n" if $CGAL eq "" && not $was_in_CGAL;
    print FO "CGAL_END_NAMESPACE\n\n"   if $CGAL ne "" && $was_in_CGAL;
    print_dynamic(@{$predicates[$i]});
    if ($want_statics) {
      print FO "#ifdef CGAL_IA_NEW_FILTERS\n\n";
      print_predicate_struct(@{$predicates[$i]});
      print_static("true", @{$predicates[$i]});
      print_static("false", @{$predicates[$i]});
      print FO "#endif // CGAL_IA_NEW_FILTERS\n\n";
      print_static_infos(@{$predicates[$i]});
    }
    $was_in_CGAL = $CGAL eq "";
  }
  print FO "CGAL_END_NAMESPACE\n\n" if $was_in_CGAL;
}

# Matches balanced $beg $end (say "(" and ")"), and counts the number
# of zones separated by a comma at level 1.
# Returns number of zones found, text before, and after.
# Perl 5.6 will support extended regexp that will understand balanced exprs...
sub extract_balanced {
  local ($beg, $end, $_) = @_;
  my $num_args = 1;	# We don't handle 0 argument functions.
  my $before = "";
  my $quote_level = 0;
  while ( /./sm ) {
    if    ($& eq $beg) { ++$quote_level; }
    elsif ($& eq $end) { --$quote_level; last if ($quote_level == 0); }
    elsif ($& eq "," && $quote_level == 1) { ++$num_args; }
    $before .= $&;
    $_ = $';
  }
  # The original text was "$before$end$_" (the last closing $end).
  return ($num_args, $before, $_);
}

# Find predicate calls in the body
# Returns the number of epsilons that this predicate needs, and the new body.
sub match_calls_in_body {
  local ($_) = @_;
  my $new_body = "";
  my $num_eps = 0;

  # We match the first call to a known predicate function.
  while (/(\W)($pred_list_re)(\s*\()/sm) {
    my $predicate_name = $2;
    my ($num_args, $before, $after) = extract_balanced ("(", ")", "(".$');

    # Recognize the actual predicate, with same number of arguments.
    my $p;
    foreach ( @predicates ) {
      $p = $_;
      last if (scalar(@$p)-$args_pos == $num_args) &&
              (@$p[$fct_name_pos] eq $predicate_name);
    }
    if (not $p) {
      warning("We matched \"$predicate_name\" with an unknown number of"
              ." arguments");
    };

    # We replace $predicate_name by
    # Static_Filtered_$predicate_name_#args::update_epsilon.
    $new_body .= "$`$1Static_Filtered_$2_$num_args\::update_epsilon$before,"
                ."\n\t\tepsilon_";

    # We add the epsilon arguments to the call in $new_body.
    $new_body.= join ",\n\t\tepsilon_", map $num_eps+$_, 0..@$p[$eps_pos]-1;
    $num_eps += @$p[$eps_pos];
    $_ = $after;
  }

  return ($num_eps, $new_body.$_);
}

# Calls match_calls_in_body over @predicates[$_], and updates $eps & $new_body.
sub treat_predicate {
  my ($i) = @_;
  my ($eps, $new_body) = match_calls_in_body($predicates[$i][$body_pos]);
  $predicates[$i][$new_body_pos] = $new_body;
  $predicates[$i][$eps_pos] = $eps;
}

# Parse the list of dependancy files, and populate @predicates with them.
sub parse_dependancy_files {
  foreach (@dependancy_files) {
    open(FI, "<$_") || die "Couldn't open dependancy file \"$_\"\n";
    parse_input_code(<FI>);
    close(FI);
  }
  # Consider them as built-in now (i.e. don't output specializations for them)
  $num_built_in_predicates=$#predicates+1;
}

# Main program
sub main {
  for ("Sign","Comparison_result","Orientation","Oriented_side","Bounded_side",
       "Angle")
  {
    $known_ret_types{$_}=1;
    $known_ret_types{"CGAL::$_"}=1;
  }
  parse_command_line();
  undef $/; # We parse the _whole_ input files as strings, not line by line.
  if ($opt_d) { parse_dependancy_files(); }
  open(FI, "<$opt_i") || die "Couldn't open input file \"$opt_i\"\n";
  my ($new_protect_name, $file_name, $rest) = parse_CGAL_header(<FI>);
  close(FI);
  parse_input_code($rest);
  open(FO, ">$opt_o") || die "Couldn't open output file \"$opt_o\"\n";
  if ($want_statics) {
    open(FL, ">$opt_l") || die "Couldn't open lib file \"$opt_l\"\n";
  }
  print_CGAL_header(FO, $new_protect_name, $file_name);
  if ($want_statics) {
    print_CGAL_header(FL, $new_protect_name."_STATIC_INFO_H",
                    "static_infos/".$file_name);
  }
  print_predicates();
  print FO "#endif // $new_protect_name\n";
  if ($want_statics) {
    print FL "#endif // $new_protect_name"."_STATIC_INFO_H\n";
  }
  close(FO);
  if ($want_statics) {
    close(FL);
  }
}

main();
