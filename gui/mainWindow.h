#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define QT_USE_FAST_CONCATENATION
#define PROG(x) cerr << x << endl

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QSizePolicy>

#include "debug.h"
#include "plotArea.h"
#include "graphwidget.h"
#include "backgroundthread.h"
#include "../src/Network.h"
#include "../src/Simulator.h";
#include "../src/Percolation_Sim.h"
#include "../src/ChainBinomial_Sim.h"

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

//Set default parameter values

const QString default_num_runs="1";
const QString default_network_size="10000";
const QString default_P0="1";
const QString default_T ="0.1";
const QString default_infectious_pd ="5";

const QString default_poi_param1 = "5.0";
const QString default_exp_param1 = "0.3";
const QString default_pow_param1 = "1.5";
const QString default_pow_param2 = "10.0";
const QString default_con_param1 = "5";

const QString generateNetMsg = "Click Generate network to begin";
const QString loadNetMsg = "Click Import edge list to begin";
const QString clearedNetMsg = "Network deleted";
const QString clearedDataMsg = "All data deleted";
const QString simulateMsg = "Click Run simulation to generate data";
const QString saveDataMsg = "Right-click on plot to save image or data";
const QString busyNetMsg = "Generating network topology . . .";
const QString busySimMsg = "Running simulation";
const QString simDoneMsg = "Simulation complete";

// Forward definitions of classes
class QMainWindow;
class QAction;
class QMainWindowButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QMenuBar;
class QPushButton;
class QTextEdit;
class QComboBox;
class QCheckBox;
class PlotArea;
class GraphWidget;
class BackgroundThread;

//Define public and private functions and slots for 'MainWindow' class
class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class BackgroundThread;

        public:
        MainWindow();

        Network* network;
        Simulator* simulator;
        GraphWidget* networkPlot;
        BackgroundThread* backgroundThread;
        QDialog* netAnalysisDialog;
        QDialog* resultsAnalysisDialog;
        QTextEdit* logEditor;
        QProgressDialog* progressDialog;

        enum DistType  { POI, EXP, POW, URB, CON};
        int rep_ct;
        vector< vector<Node*> > netComponents;
        void updateProgress(int x);

    signals:
        void progressUpdated(int);
    
    public slots:
        // Parameter slots 
        void changeNetSource(int source);
        void defaultNetworkParameters();
        void changeNetworkParameters(int dist_type);
        void changeSimType(int type);
        bool validateParameters(); // currently only transmissibility
        void updateRZero();
        void defaultSettings();

        // Network creation/deletion slots
        void generate_network_thread();
        bool generate_network();
        bool connect_network (Network* net, DistType dist, double param1, double param2);
        void netDoneUpdate(bool success);
        void readEdgeList();
        void saveEdgeList();
        void clear_network();

        // Simulation slots
        void simulatorWrapper();
        void clear_data();
        void generate_sim_thread();

        // Plot update slots
        void updateNetworkPlot();
        void updatePlotMenuFlags();
        void showHideStatePlot();
        void showHideEpiCurvePlot();
        void showHideHistPlot();
        void plotNetwork();

        // Network analysis slots
        void analyzeNetwork();
        void generate_comp_thread();
        void calculateComponentStats();
        void removeMinorComponents();
        void generate_trans_thread();
        void calculateTransitivity();
        void generate_dist_thread();
        void calculateDistances();

        // Misc
        void appendOutput(QString);
        void appendOutputLine(QString);
        void stopBackgroundThread();
        void resetCursor();
        void enableCentralWidget();
        void disableCentralWidget();
        void analyzeResults();
        void updateResultsAnalysis();
 
    protected:

    private:

       // void updateNetProcessProgress();

        
        // Menu bar
        QMenu* fileMenu;
        QAction* exitAction;
        QAction* openAction;
        
        QMenu* plotMenu;
        QAction* showStatePlot;
        QAction* showEpiPlot;
        QAction* showHistPlot;

        // Central widget
        QWidget* centralWidget;
        QGroupBox* mainBox;
        QMenuBar* menuBar;
        void createMenu();
        QWidget* leftBox;
        QTabWidget* tabWidget;
        QSplitter* rightBox;

        // Network settings
        QWidget* networkSettingsGroupBox;
        void createNetworkSettingsBox();
        QLabel* netsourceLabel;
        QComboBox* netsourceBox;
        QLabel* distLabel;
        QComboBox* distBox;

        QLabel* param1Label;
        QLineEdit* poiLambdaLine;
        QLineEdit* expBetaLine;
        QLineEdit* powAlphaLine;
        QLineEdit* conValueLine;

        QLabel* param2Label;
        QLineEdit* powKappaLine;

        QLabel* netfileLabel;
        QLineEdit* netfileLine;
        QLineEdit* numnodesLine;


        // Simulator settings
        QWidget* simulatorSettingsGroupBox;
        void createSimulatorSettingsBox();
        QLabel* simLabel;
        QComboBox* simBox;
        QLabel* infectiousPeriodLabel;
        QLineEdit* pzeroLine;
        QLineEdit* transLine;
        QLineEdit* infectiousPeriodLine;
        QLineEdit* numrunsLine;
        
        // Control panel
        QGroupBox* controlButtonsGroupBox;
        void createControlButtonsBox();
        QPushButton* clearNetButton;
        QPushButton* defaultSettingsButton;
        QPushButton* loadNetButton;
        QPushButton* generateNetButton;
        QPushButton* clearDataButton;
        //QPushButton* helpButton;
        QPushButton* analyzeNetButton;
        QPushButton* runSimulationButton;
        QCheckBox* retainDataCheckBox;

        // Predictions panel
        QGroupBox* predictionsGroupBox;
        void createPredictionsBox();
        QLineEdit* rzeroLine;
        QLineEdit* maPredictionLine;
        QLineEdit* netPredictionLine;

        // Main plots
        void createPlotPanel();
        PlotArea* epiCurvePlot;
        PlotArea* statePlot;
        PlotArea* histPlot;
        
        void addStateData();

        // Network analysis dialog
        void createNetworkAnalysis();
        void _addNetAnalysisRow(QGridLayout* layout, QString label, QLineEdit* box, QPushButton* button = NULL);

        QLineEdit* nodeCountEdit;
        QLineEdit* edgeCountEdit;
        QLineEdit* meanDegreeEdit;
        QLineEdit* componentCountEdit;
        QLineEdit* maxComponentSizeEdit;
        QLineEdit* transitivityEdit;
        QLineEdit* diameterEdit;
        QLineEdit* meanDistanceEdit;

        QPushButton* componentButton1;
        QPushButton* componentButton2;
        QPushButton* transitivityButton;
        QPushButton* diameterButton;
        QPushButton* meanDistanceButton;

        PlotArea* degDistPlot;

        // Results analysis dialog
        void createResultsAnalysis();
        void _addResultsAnalysisRow(QGridLayout* layout, QString label, QLineEdit* n, QLineEdit* min, QLineEdit* max, QLineEdit* mean, QLineEdit* sd);

        QLineEdit* thresholdEdit;
        
        QLineEdit* outNEdit;
        QLineEdit* outMeanEdit;
        QLineEdit* outSDEdit;
        QLineEdit* outMinEdit;
        QLineEdit* outMaxEdit;
        
        QLineEdit* epiNEdit;
        QLineEdit* epiMeanEdit;
        QLineEdit* epiSDEdit;
        QLineEdit* epiMinEdit;
        QLineEdit* epiMaxEdit;
        
        QLineEdit* allNEdit;
        QLineEdit* allMeanEdit;
        QLineEdit* allSDEdit;
        QLineEdit* allMinEdit;
        QLineEdit* allMaxEdit;


        // Network plot
    
        //QMainWindowButtonBox* buttonBox;
     

        // Helper functions
        double calculate_T_crit();
        double getPercTransmissibility();
        double convertR0toT(double R0);
        double convertTtoR0(double T);
        double convertTtoTCB (double T, int d);
        double convertTCBtoT (double TCB, int d);
        double maExpectedSize(double R0, double P0_frac, double guess);
        double netExpectedSize(double T, double P0_frac);
        int find_epi_threshold(vector<int> data);
        
        void makeEditable(QLineEdit* lineEdit);
        void makeReadonly(QLineEdit* lineEdit);
        int percent_complete(int current, double predicted);


        

};
#endif
