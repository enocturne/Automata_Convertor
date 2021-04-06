/*
######Automata_Convertor######
v0.1
*/
import 'dart:io';

void main(List<String> arguments) async {
  stdout.write("Input the path of the NFA file:\n");
  String? iptfilepath;
  do {
    iptfilepath = stdin.readLineSync();
  } while (iptfilepath == null);
  File iptfile = new File(iptfilepath);
  List<String> iptcontent = await iptfile.readAsLinesSync();
  if (iptcontent.length < 4) {
    stderr.writeln('Fatal Error.');
    return;
  }
  var iptNFA = NFA(iptcontent);
  stdout.write("Input the path of the DFA file:\n");
  String? optfilepath;
  do {
    optfilepath = stdin.readLineSync();
  } while (optfilepath == null);
  File optfile = new File(optfilepath);
}

class FiniteAutomata {
  List<String> Q = ['q0', 'q1']; //Collection of states.
  List<String> T = ['0', '1']; //Collection of inputs.
  Map<String, List<String>> transfunc = {
    'q00': ['q1'],
    'q01': ['q1'],
    'q10': ['q1'],
    'q11': ['q1'],
  }; //Transform functions.
  String q0 = 'q0'; //Initial state.
  List<String> F = ['q1']; //Collection of ending states.
}

class NFA extends FiniteAutomata {
  NFA(List<String> content) {
    Q = content[0].split(';');
    T = content[1].split(';');
    List<String> temp = content[2].split(';');
    q0 = temp[0];
    F = temp.sublist(1);
    for (int i = 3; i < content.length; i++) {
      temp = content[i].split(';');
      transfunc[temp[0] + temp[1]] = temp.sublist(2);
    }
  }
}

class DFA extends FiniteAutomata {
  DFA(NFA iptauto) {
    Q = iptauto.Q;
    T = iptauto.T;
    q0 = iptauto.q0;
    F = iptauto.F;
    transfunc = iptauto.transfunc;
    bool trigger = false;
    do {
      transfunc.forEach((key, value) {
        if (value.length > 1) {
          trigger = true;
          int count = 0;
          value.forEach((element) {
            if (F.contains(element)) {
              count++;
            }
          });
          if (count == value.length) {
            F.add(value.join(','));
          }
        }
      });
    } while (trigger);
  }
}
