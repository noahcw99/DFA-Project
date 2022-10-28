# DFA-Project
Tests for valid email addresses using a deterministic finite automaton (DFA).
Compile and run emailDFA.cpp to test program. No bugs in current state
Visual Representation of DFA provided in DFA.jpg

Program to build DFA that tests for a valid email
Valid Emails are defined as:
          ((Γ*)Δ(Γ*)*) Ø ((Γ*)Δ(Γ*)*) ('o' || 'c') ('r' || 'o') ('g' || 'm')

Where Γ is any letter from 'a-z' or number from '0-9', Δ is '.', Ø is '@',
          * notates infinite of that thing can be used,
          || notates an option between multiple things

Images for visual representation DFA attatched on github

Examples of valid emails:
          foo.bar99@fun.com, this5.will4.work3.even2@like1.this0.org, 
          555555555555this@too9999999999999999.com

Examples of invalid emails:
          this..wont@work.org, sad@toomany..com, needs.org.or.com@end.ze, 
          missing.symbol.com, invalid^symbol@here.com
         
         
