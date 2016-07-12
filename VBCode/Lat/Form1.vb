Public Class Form1

    Dim CARACTER As Integer
    Private Declare Function LockWindowUpdate Lib "user32" (ByVal hWnd As Integer) As Integer



    Private Sub ArchivoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ArchivoToolStripMenuItem.Click

    End Sub

    Private Sub FechaToolStripMenuItem_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub GuardarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GuardarToolStripMenuItem.Click
        Dim lat As New SaveFileDialog()
        lat.Filter = "Código latino|*.lat"
        If (lat.ShowDialog() = System.Windows.Forms.DialogResult.OK) _
            And (lat.FileName.Length) > 0 Then
            RichTextBox1.SaveFile(lat.FileName, RichTextBoxStreamType.PlainText)
        End If
    End Sub

    Private Sub PegarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PegarToolStripMenuItem.Click
        RichTextBox1.Paste()
    End Sub

    Private Sub NuevoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NuevoToolStripMenuItem.Click
        Dim newform = New Form1
        newform.Text = "Latino Editor - Sin título"
        newform.Show()
    End Sub

    Private Sub AbrirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AbrirToolStripMenuItem.Click
        If (OpenFileDialog1.FileName = "OpenFileDialog1") Then
            OpenFileDialog1.FileName = ""
        End If

        OpenFileDialog1.DefaultExt = ".lat"
        OpenFileDialog1.Filter = String.Format("
Código latino|*.lat|
Archivo de texto|*.txt|
Todos los archivos|*.*|
|")
        OpenFileDialog1.Title = "Latino Editor"
        If (OpenFileDialog1.ShowDialog = DialogResult.OK) Then
            RichTextBox1.Text = My.Computer.FileSystem.ReadAllText(OpenFileDialog1.FileName,
                                                                   System.Text.Encoding.UTF7)
        End If

        Text = OpenFileDialog1.FileName


    End Sub

    Private Sub ImprimirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ImprimirToolStripMenuItem.Click
        PrintDialog1.ShowDialog()
    End Sub

    Private Sub SalirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SalirToolStripMenuItem.Click
        If MessageBox.Show("¿Estás seguro de que quieres salir?", "Latino Editor",
         MessageBoxButtons.YesNo, MessageBoxIcon.Question) _
         = DialogResult.Yes Then
            Application.Exit()
        End If
    End Sub

    Private Sub CortarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CortarToolStripMenuItem.Click
        RichTextBox1.Cut()
    End Sub

    Private Sub CopiarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopiarToolStripMenuItem.Click
        RichTextBox1.Copy()
    End Sub

    Private Sub DeshacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DeshacerToolStripMenuItem.Click
        RichTextBox1.Undo()
    End Sub

    Private Sub RehacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RehacerToolStripMenuItem.Click
        RichTextBox1.Redo()
    End Sub

    Private Sub LimpiarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LimpiarToolStripMenuItem.Click
        RichTextBox1.Clear()
    End Sub

    Private Sub SeleccionarTodoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SeleccionarTodoToolStripMenuItem.Click
        RichTextBox1.SelectAll()
    End Sub

    Private Sub ImprimirFechaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ImprimirFechaToolStripMenuItem.Click
        RichTextBox1.AppendText(Date.Now.ToString)
    End Sub



    Private Sub CopiarTodoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopiarTodoToolStripMenuItem.Click
        RichTextBox1.SelectAll()
        RichTextBox1.Copy()
        RichTextBox1.DeselectAll()
    End Sub

    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        Timer1.Interval = 10
        Timer1.Start()
    End Sub

    Private Sub Timer1_Tick(sender As System.Object, e As System.EventArgs) Handles Timer1.Tick
        PictureBox1.Refresh()
    End Sub

    Private Sub PictureBox1_Paint(sender As Object, e As System.Windows.Forms.PaintEventArgs) Handles PictureBox1.Paint

        CARACTER = 0
        Dim ALTURA As Integer = RichTextBox1.GetPositionFromCharIndex(0).Y

        If RichTextBox1.Lines.Length > 0 Then
            For I = 0 To RichTextBox1.Lines.Length - 1
                e.Graphics.DrawString(I + 1, RichTextBox1.Font, Brushes.Black, PictureBox1.Width - (e.Graphics.MeasureString(I + 1, RichTextBox1.Font).Width - 1), ALTURA)
                CARACTER += RichTextBox1.Lines(I).Length + 1
                ALTURA = RichTextBox1.GetPositionFromCharIndex(CARACTER).Y
            Next
        Else
            e.Graphics.DrawString(1, RichTextBox1.Font, Brushes.Black, PictureBox1.Width - (e.Graphics.MeasureString(1, RichTextBox1.Font).Width - 1), ALTURA)
        End If
    End Sub

    Private Sub TotalToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles TotalToolStripMenuItem.Click

        Dim lines As Integer = RichTextBox1.Lines.Count
        If lines = 0 Then
            MsgBox("Este código no tiene lineas (" & lines & ")")
        Else
            MsgBox("Este código tiene " & lines & " lineas.")
        End If
    End Sub

    Private Sub PictureBox1_Click(sender As Object, e As EventArgs) Handles PictureBox1.Click

    End Sub

    Private Sub RichTextBox1_TextChanged(sender As System.Object, e As System.EventArgs) Handles RichTextBox1.TextChanged
        RichTextBox1.Multiline = True
        RichTextBox1.AcceptsTab = True
    End Sub




    Private Sub SitioWebToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SitioWebToolStripMenuItem.Click
        Dim pagina As String
        pagina = "http://lenguaje-latino.org/"
        Shell("explorer " & pagina)
    End Sub

    Private Sub GitHubToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GitHubToolStripMenuItem.Click
        Dim github As String
        github = "https://github.com/primitivorm/latino"
        Shell("explorer " & github)
    End Sub

    Private Sub SoporteToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SoporteToolStripMenuItem.Click
        Dim soporte As String
        soporte = "https://gitter.im/primitivorm/latino"
        Shell("explorer " & soporte)
    End Sub

    Private Sub HerramientasToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles HerramientasToolStripMenuItem.Click

    End Sub

End Class