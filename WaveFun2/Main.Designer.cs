namespace WaveFun
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnGenerateWave = new System.Windows.Forms.Button();
            this.cbWaveType = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tbFileLocation = new System.Windows.Forms.TextBox();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.sldFrequency = new System.Windows.Forms.TrackBar();
            this.lblFrequency = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lblVolume = new System.Windows.Forms.Label();
            this.sldVolume = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.sldFrequency)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sldVolume)).BeginInit();
            this.SuspendLayout();
            // 
            // btnGenerateWave
            // 
            this.btnGenerateWave.Enabled = false;
            this.btnGenerateWave.Location = new System.Drawing.Point(12, 310);
            this.btnGenerateWave.Name = "btnGenerateWave";
            this.btnGenerateWave.Size = new System.Drawing.Size(241, 50);
            this.btnGenerateWave.TabIndex = 1;
            this.btnGenerateWave.Text = "Generate Wave";
            this.btnGenerateWave.UseVisualStyleBackColor = true;
            this.btnGenerateWave.Click += new System.EventHandler(this.btnGenerateWave_Click);
            // 
            // cbWaveType
            // 
            this.cbWaveType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbWaveType.FormattingEnabled = true;
            this.cbWaveType.Items.AddRange(new object[] {
            "Sine",
            "Square",
            "Sawtooth",
            "Triangle",
            "White Noise"});
            this.cbWaveType.Location = new System.Drawing.Point(15, 121);
            this.cbWaveType.Name = "cbWaveType";
            this.cbWaveType.Size = new System.Drawing.Size(229, 21);
            this.cbWaveType.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 105);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(63, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Wave Type";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 165);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Frequency (Hz):";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(91, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Save WAV file to:";
            // 
            // tbFileLocation
            // 
            this.tbFileLocation.Location = new System.Drawing.Point(12, 25);
            this.tbFileLocation.Name = "tbFileLocation";
            this.tbFileLocation.ReadOnly = true;
            this.tbFileLocation.Size = new System.Drawing.Size(241, 20);
            this.tbFileLocation.TabIndex = 7;
            this.tbFileLocation.Text = "(Click Browse)";
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point(12, 51);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(75, 23);
            this.btnBrowse.TabIndex = 8;
            this.btnBrowse.Text = "Browse...";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // sldFrequency
            // 
            this.sldFrequency.LargeChange = 100;
            this.sldFrequency.Location = new System.Drawing.Point(7, 181);
            this.sldFrequency.Maximum = 2000;
            this.sldFrequency.Minimum = 40;
            this.sldFrequency.Name = "sldFrequency";
            this.sldFrequency.Size = new System.Drawing.Size(237, 45);
            this.sldFrequency.SmallChange = 10;
            this.sldFrequency.TabIndex = 9;
            this.sldFrequency.TickFrequency = 500;
            this.sldFrequency.TickStyle = System.Windows.Forms.TickStyle.None;
            this.sldFrequency.Value = 440;
            this.sldFrequency.Scroll += new System.EventHandler(this.tbFrequency_Scroll);
            // 
            // lblFrequency
            // 
            this.lblFrequency.AutoSize = true;
            this.lblFrequency.Location = new System.Drawing.Point(100, 165);
            this.lblFrequency.Name = "lblFrequency";
            this.lblFrequency.Size = new System.Drawing.Size(25, 13);
            this.lblFrequency.TabIndex = 10;
            this.lblFrequency.Text = "440";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 229);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(45, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Volume:";
            // 
            // lblVolume
            // 
            this.lblVolume.AutoSize = true;
            this.lblVolume.Location = new System.Drawing.Point(63, 229);
            this.lblVolume.Name = "lblVolume";
            this.lblVolume.Size = new System.Drawing.Size(33, 13);
            this.lblVolume.TabIndex = 12;
            this.lblVolume.Text = "100%";
            // 
            // sldVolume
            // 
            this.sldVolume.LargeChange = 10;
            this.sldVolume.Location = new System.Drawing.Point(12, 245);
            this.sldVolume.Maximum = 100;
            this.sldVolume.Minimum = 10;
            this.sldVolume.Name = "sldVolume";
            this.sldVolume.Size = new System.Drawing.Size(237, 45);
            this.sldVolume.TabIndex = 13;
            this.sldVolume.TickFrequency = 500;
            this.sldVolume.TickStyle = System.Windows.Forms.TickStyle.None;
            this.sldVolume.Value = 100;
            this.sldVolume.Scroll += new System.EventHandler(this.sldVolume_Scroll);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(265, 372);
            this.Controls.Add(this.sldVolume);
            this.Controls.Add(this.lblVolume);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lblFrequency);
            this.Controls.Add(this.sldFrequency);
            this.Controls.Add(this.btnBrowse);
            this.Controls.Add(this.tbFileLocation);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.cbWaveType);
            this.Controls.Add(this.btnGenerateWave);
            this.Name = "frmMain";
            this.Text = "Wave Generator";
            ((System.ComponentModel.ISupportInitialize)(this.sldFrequency)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sldVolume)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnGenerateWave;
        private System.Windows.Forms.ComboBox cbWaveType;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbFileLocation;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.TrackBar sldFrequency;
        private System.Windows.Forms.Label lblFrequency;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lblVolume;
        private System.Windows.Forms.TrackBar sldVolume;
    }
}

