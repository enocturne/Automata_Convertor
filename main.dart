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
  List Q = []; //Collection of states.
  List T = []; //Collection of inputs.
  List transfunc = []; //Transform functions.
  String q0 = 'q0'; //Initial state.
  List F = []; //Collection of ending states.
}

class NFA extends FiniteAutomata {
  NFA(List<String> content) {
    Q = content[0].split(','); //read Q.
    T = content[1].split(','); //read T.
    T.forEach((_) => transfunc.add(List.generate(
        Q.length,
        (_) => List.generate(Q.length,
            (_) => 0)))); //generate the matrixes of transform functions.
    List temp = content[2].split(','); //a temporary list。
    q0 = temp[0]; //read q0.
    F = temp.sublist(1); //read F.
    var j = 0; //column pointer.
    content.sublist(3).forEach((column) {
      temp.clear();
      column.split(',').forEach((element) {
        temp.add(int.parse(element));
      });
      transfunc[j ~/ Q.length][j % Q.length] = temp;
      j++;
    });
  }
}
