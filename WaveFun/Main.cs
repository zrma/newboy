//-----------------------------------------------------
// Main.cs
// Code for the main form of this app.
//
// Copyright (c) 2009 Dan Waters
// This code is provided AS-IS and is written by me,
// with no endorsement from Microsoft.
//-----------------------------------------------------

using System;
using System.Windows.Forms;
using System.Media;

namespace WaveFun
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private void btnGenerateWave_Click(object sender, EventArgs e)
        {
            string filePath = @"Z:\Downloads\Sine.wav";
            // Output file path setting

            WaveGenerator wave = new WaveGenerator(WaveExampleType.ExampleSineWave);
            wave.Save(filePath);

            SoundPlayer player = new SoundPlayer(filePath);               
            player.Play();
        }
    }
}
