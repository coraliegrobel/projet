class Total_Sequences{
  private:;
    size_t counter(0); //to create the frameshifts
    vecotr<char> motif;
    vector<double> values; //the binding values
    vector<vector<double>> matrix;
    string nom_fasta;
    string nom_matrix;
    string nom_taux;

  public:
  void create_matrix();
  void run(); //ou se deroule le process de voir chaque sequence
  double calculate_value();
  double calculate_reverse_value();
  void add_char(); //supprime le premier et ajoute un character dans motif




}
