hrkconfig-define emacs-autocomplete \
    -output {
	puts "Generating .dir-locals.el ..."
	set fp [open .dir-locals.el wb]
	puts $fp "("
	# Autocomplete.
	# -target i686-w64-mingw32
	
	foreach var {
	    company-clang-arguments
	    flycheck-clang-args
	    flycheck-gcc-args
	} {
	    puts $fp "(nil . (($var . ("
	    foreach l [hrkconfig-add-parsers] { puts $fp \"$l\" }
	    switch -regexp $var {
		clang { puts $fp "\"-target\" \"[hrkconfig-get HOST]\""  }
	    }
	    puts $fp "))))"
	}
	# Flycheck.
	foreach varval {
	    { c++-mode flycheck-c/c++-gcc-executable   var CXX }
	    { c-mode   flycheck-c/c++-gcc-executable   var CC  }
	    { c++-mode flycheck-c/c++-clang-executable var CXX }
	    { c-mode   flycheck-c/c++-clang-executable var CC  }

	    { c++-mode     flycheck-checker      val c/c++-gcc }
	    { c-mode       flycheck-checker      val c/c++-gcc }
	    { company-mode company-async-timeout val 10        }
	} {
	    set mode [lindex $varval 0]
	    set var  [lindex $varval 1]
	    switch [lindex $varval 2] {
		var {
		    set val [lindex $varval 3]
		    if {[hrkconfig-exists $val] == 0} continue
		    set val \"[hrkconfig-get $val]\"
		}
		val {
		    set val [lindex $varval 3]
		}
	    }
	    puts $fp "($mode . (($var . $val)))"
	}
	puts $fp ")"
	close $fp
	
    }
